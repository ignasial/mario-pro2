#include "game.hh"
#include "utils.hh"
#include <iostream>
#include <cstdlib>

using namespace pro2;  
using namespace std;

Game::Game(int width, int height, int enemy_count)
    : mario_({200, 150}),
      platforms_{
          Platform(150, 255, 240, 350),
          Platform(930, 1100, 240, 350),
      },
      coins_{
          Coin({215, 240}),
          Coin({1005, 237}),
          Coin({1015, 237}),
          Coin({1040, 237}),
      },
      paused_(false),
      finished_(false),
      count_coin(0),
      root_checkpoint_(NULL),
      current_checkpoint_(NULL),
      current_frame_(0)
{
    add_checkpoint(625, 205);
    add_checkpoint(825, 195);
    add_checkpoint(800, 270);
    add_checkpoint(1020, 240);

    current_checkpoint_ = NULL;
    initial_position_ = mario_.pos();

    for (int i = 0; i < 3; ++i) {
        lives_.push(i);
    }

    /**
     * CASO DE PRUEBA INTERESANTE: 
     * -Entrada: probar con N muy grande
     * -Comportamiento: se espera que el juego siga fluido
     */
    int N = 3;
    for (int i = 0; i < N; i++) {
        platforms_.push_back(Platform(330 + i*200, 480 + i *200, 215 - 10*i, 225 -10*i));
        coins_.push_back(Coin({415 + i * 200, 213 - 10*i}));
        
    }
    for (int i = 0; i < 3; ++i) {
        platforms_.push_back(Platform(280 + i*200, 500 + i*200, 270, 350));
        coins_.push_back(Coin({415 + i * 200, 267}));
    }
    for (int i = 0; i < enemy_count; ++i) {
        int base_x = 400 + i * 200;
        int left_limit = base_x - 10;
        int right_limit = base_x + 10;
        enemies_.emplace_back(Pt{base_x, 220 - 10*i}, left_limit, right_limit);
        enemy_finder_.add(&enemies_.back());
    }

    for (Platform& platform : platforms_) {
        platform_finder_.add(&platform);
    }

    for (Coin& coin : coins_) {
        coin_finder_.add(&coin);
    }
}

Game::~Game() {
    delete root_checkpoint_;
}

void Game::add_checkpoint(int x, int y) {
    Checkpoint* cp = new Checkpoint(x, y);
    if (root_checkpoint_ == NULL) {
        root_checkpoint_ = cp;
    } else {
        root_checkpoint_->insert(cp);
    }
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if (window.was_key_pressed('P')) {
        paused_ = !paused_;
        message_queue_.push(paused_ ? "Juego pausado" : "Juego reanudado", 120);
    }
}

void Game::update(pro2::Window& window) {
    Pt camera_center = window.camera_center();
    Rect visible_area = {
        camera_center.x - window.width() / 2,
        camera_center.y - window.height() / 2,
        camera_center.x + window.width() / 2,
        camera_center.y + window.height() / 2
    };

    visible_platforms_ = platform_finder_.query(visible_area);
    visible_coins_.clear();
    for (const Coin* c : coin_finder_.query(visible_area)) {
        visible_coins_.insert(const_cast<Coin*>(c));
    }

    process_keys(window);

    visible_enemies_.clear();
    auto const_visible_enemies = enemy_finder_.query(visible_area);
    for (Enemy const* e : const_visible_enemies) {
        visible_enemies_.insert(const_cast<Enemy*>(e));
    }

    if (!paused_ && !finished_) {
        update_objects(window);
        update_camera(window);

        ++current_frame_;
        message_queue_.update();
    }
}

void Game::update_objects(pro2::Window& window) {
    Pt camera_center = window.camera_center();
    Rect visible_area = {
        camera_center.x - window.width() / 2,
        camera_center.y - window.height() / 2,
        camera_center.x + window.width() / 2,
        camera_center.y + window.height() / 2
    };

    mario_.update(window, platforms_);

    if (root_checkpoint_ != NULL) {
        Checkpoint* closest_cp = root_checkpoint_->find_closest(mario_.pos().x, mario_.pos().y);
        if (closest_cp != NULL) {
            Rect mario_rect = mario_.get_rect();
            Rect cp_rect = closest_cp->get_rect();

            if (rects_solapan(mario_rect, cp_rect)) {
                current_checkpoint_ = closest_cp;
            }
        }
    }

    if (mario_.pos().y > 1000) {
        message_queue_.push("¡Has caído! Pierdes una vida.", 120);
        reset_mario(window);
        return;
    }

    auto const_visible_coins = coin_finder_.query(visible_area);
    visible_coins_.clear();
    for (const Coin* coin_ptr : const_visible_coins) {
        Coin* coin_nc = const_cast<Coin*>(coin_ptr);
        coin_nc->update(window);

        if (!coin_nc->is_collected() && rects_solapan(mario_.get_rect(), coin_nc->get_rect())) {
            coin_nc->collect();
            ++count_coin;
            if (!coin_nc->message_shown()) {
                message_queue_.push("Moneda recogida, tienes " + std::to_string(count_coin) + " monedas.", 120);
                coin_nc->set_message_shown(true);
            }
        }

        visible_coins_.insert(coin_nc);
    }

    auto it = enemies_.begin();
    while (it != enemies_.end()) {
        Enemy* enemy_nc = &(*it);
        enemy_nc->update(window);

        if (!enemy_nc->is_alive()) {
            enemy_finder_.remove(enemy_nc);
            it = enemies_.erase(it);
        } else {
            if (rects_solapan(enemy_nc->get_rect(), mario_.get_rect())) {
                reset_mario(window);
            }
            ++it;
        }
    }
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = (pos.x > right) ? (pos.x - right) : (pos.x < left ? (pos.x - left) : 0);
    int dy = (pos.y < top) ? (pos.y - top) : (pos.y > bottom ? (pos.y - bottom) : 0);

    window.move_camera({dx, dy});
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);

    for (const Platform* p : visible_platforms_) {
        p->paint(window);
    }

    for (const Coin* s : visible_coins_) {
        s->paint(window);
    }

    for (const Enemy* e : visible_enemies_) {
        e->paint(window);
    }
    if (root_checkpoint_ != NULL) {
        root_checkpoint_->paint(window);
    }

    mario_.paint(window);

}

void Game::reset_mario(pro2::Window& window) {
    Pt respawn_pos = initial_position_;
    if (current_checkpoint_ !=  NULL) {
        respawn_pos = {current_checkpoint_->x, current_checkpoint_->y};
    }

    mario_.set_pos(respawn_pos);
    mario_.reset_speed();

    int cam_x = respawn_pos.x - window.width() / 2;
    int cam_y = respawn_pos.y - window.height() / 2 - 255;
    if (cam_x < 0) cam_x = 0;
    if (cam_y < 0) cam_y = 0;

    window.set_camera_topleft({cam_x, cam_y});

    if (!lives_.empty()) {
        lives_.pop();
    }

    message_queue_.push("¡Has perdido una vida! Vidas restantes: " + std::to_string(lives_.size()));

    if (lives_.empty()) {
        finished_ = true;
        message_queue_.push("GAME OVER: No te quedan vidas. Puntuación total: " + std::to_string(count_coin));
    }
}

std::list<Enemy>& Game::enemies() {
    return enemies_;
}

std::list<Coin>& Game::coins() {
    return coins_;
}

Finder<Enemy>& Game::enemy_finder() {
    return enemy_finder_;
}

Finder<Coin>& Game::coin_finder() {
    return coin_finder_;
}

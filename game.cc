#include "game.hh"
#include "utils.hh"

using namespace pro2;
using namespace std;

Game::Game(int width, int height, int enemy_count)
    : mario_({width / 2, 150}),
      platforms_{
          Platform(100, 300, 250, 331),
          Platform(0, 200, 250, 331),
          Platform(250, 400, 250, 331),
      },
      coins_{
        Coin({200, 248}),
      },
      paused_(false),
      finished_(false),
      game_over_(false) {

    initial_position_ = mario_.pos();

    // Inicializa el stack de vidas con 3 vidas (3, 2, 1)
    for (int i = 0; i < 3; ++i) {
        lives_.push(i);
    }

    for (int i = 0; i < 40000; i++) {
        platforms_.push_back(Platform(250 + i * 200, 470 + i * 200, 250, 331));
        coins_.emplace_back(Coin({300 + i * 200, 249}));
    }
    for (int i = 0; i < enemy_count; ++i) {
        int base_x = 400 + i * 100;
        int left_limit = base_x - 30;
        int right_limit = base_x + 30;
        enemies_.emplace_back(Pt{base_x, 252}, left_limit, right_limit);
        enemy_finder_.add(&enemies_.back());
    }

    for (Platform& platform : platforms_) {
        platform_finder_.add(&platform);
    }

    for (Coin& coin : coins_) {
        coin_finder_.add(&coin);
    }
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
    if (window.was_key_pressed('P')) {
        paused_ = !paused_;
        return;
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
    visible_coins_ = coin_finder_.query(visible_area);

    process_keys(window);

    // Actualizamos visible_enemies_ siempre para pintar incluso en pausa
    visible_enemies_.clear();
    auto const_visible_enemies = enemy_finder_.query(visible_area);
    for (Enemy const* e : const_visible_enemies) {
        visible_enemies_.insert(const_cast<Enemy*>(e));
    }

    if (!paused_ && !finished_) {
        update_objects(window);
        update_camera(window);
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

    // Daño por caída al caer por debajo de Y=1000
    if (mario_.pos().y > 1000) {
        cout << "¡Has caído! Pierdes una vida." << endl;
        reset_mario();
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
            cout << "Moneda recogida, tienes " << count_coin << " monedas." << endl;
        }

        visible_coins_.insert(coin_nc);
    }

    // Actualizamos enemigos vivos y eliminamos muertos
    auto it = enemies_.begin();
    while (it != enemies_.end()) {
        Enemy* enemy_nc = &(*it);
        enemy_nc->update(window);

        if (!enemy_nc->is_alive()) {
            enemy_finder_.remove(enemy_nc);
            it = enemies_.erase(it);
        } else {
            // Daño al tocar un enemigo
            if (rects_solapan(enemy_nc->get_rect(), mario_.get_rect())) {
                reset_mario();
                return;
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

    mario_.paint(window);
}

void Game::reset_mario() {
    mario_.set_pos(initial_position_);
    mario_.reset_speed();

    if (!lives_.empty()) {
        lives_.pop();
    }

    cout << "¡Has perdido una vida! Vidas restantes: " << lives_.size() << endl;

    if (lives_.empty()) {
        finished_ = true;
        if (!game_over_) {
            cout << "GAME OVER: No te quedan vidas. Puntuación total: " << count_coin << endl;
            game_over_ = true;
        }
    }
}

#include "game.hh"
#include "utils.hh"
#include "geometry.hh"
#include "enemy.hh"
#include <vector>
#include <iostream>

using namespace pro2;
using namespace std;

Game::Game(int width, int height)
    : mario_({100, 100}),
      platforms_{
          //Platform(0, 300, 256, 355),
          Platform(50, 150, 100, 120),
      },
      enemies_{
          Enemy({200, 210}, 350, 450)
      },
      coins_{
          Coin({200, 200}),
          Coin({100, 250}),
          Coin({300, 150}),
      },
      paused_(false),
      finished_(false),
      lifes(3),
      count_coin(0) {

    for (int i = 1; i < 4; i++) {
        platforms_.push_back(Platform(100 + i * 100, 100 + i * 300, 256, 355));
        coins_.push_back(Coin({300 + i * 200, 250}));
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
        camera_center.y + window.height() / 2};

    visible_platforms_ = platform_finder_.query(visible_area);
    visible_coins_ = coin_finder_.query(visible_area);

    process_keys(window);

    if (!paused_) {
        update_objects(window);
        update_camera(window);
    }

    is_death();
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);

    for (Enemy& enemy : enemies_) {
        enemy.update(window);
    }

    for (Enemy& enemy : enemies_) {
        if ((enemy.is_alive() && mario_.is_alive() && rects_solapan(enemy.get_rect(), mario_.get_rect())) || (mario_.get_rect().bottom == 400)) {
            mario_.kill();
            cout << "Mario ha muerto. Vidas restantes: " << lifes << endl;
        }
    }

    visible_coins_.clear();
    auto const_visible = coin_finder_.query(Rect{
        window.camera_center().x - window.width() / 2,
        window.camera_center().y - window.height() / 2,
        window.camera_center().x + window.width() / 2,
        window.camera_center().y + window.height() / 2
    });

    for (const Coin* s : const_visible) {
        Coin* non_const_s = const_cast<Coin*>(s);
        non_const_s->update(window);

        if (!non_const_s->is_collected() && rects_solapan(mario_.get_rect(), non_const_s->get_rect())) {
            non_const_s->collect();
            ++count_coin;
            cout << "Moneda recogida. Cantidad total: " << count_coin << endl;
        }

        visible_coins_.insert(non_const_s);
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
    window.clear(0x87CEEB); //sky  blue

    for (const Platform* p : visible_platforms_) {
        p->paint(window);
    }

    for (const Coin* s : visible_coins_) {
        s->paint(window);
    }

    for (Enemy& enemy : enemies_) {
        enemy.paint(window);
    }

    mario_.paint(window);
}

void Game::is_death() {
    if (!mario_.is_alive()) {
        lifes--;
        if (lifes >= 0) {
            mario_.respawn();
        } else {
            finished_ = true;
            cout << "GAME OVER" << endl;
        }
    }
}

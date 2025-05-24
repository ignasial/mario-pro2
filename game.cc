#include "game.hh"
#include "utils.hh"
#include "geometry.hh"

using namespace pro2;
using namespace std;

Game::Game(int width, int height)
    : mario_({width / 2, 150}),
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      coins_{
        Coin({200, 200}),
        Coin({100, 250}),
        Coin({300, 150}),
      },
      paused_(false),
      finished_(false) {

    for (int i = 1; i < 40000; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
        coins_.push_back(Coin({300 + i *200, 150}));
       
    }

    //Añadimos las plataformas al finder
    for (Platform& platform : platforms_) {
        platform_finder_.add(&platform);
    }
    
    //Hacemos lo mismo con las monedas
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
    //Creamos rectangulo con el area visible actual
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

    if (!paused_) {
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

    auto const_visible = coin_finder_.query(visible_area);
    visible_coins_.clear();

    for (const Coin* s : const_visible) {
        Coin* non_const_s = const_cast<Coin*>(s);
        non_const_s->update(window);

        if (!non_const_s->is_collected() && rects_solapan(mario_.get_rect(), non_const_s->get_rect())) {
            non_const_s->collect();
            ++count_coin;
            cout << "Moneda recollida, tens " << count_coin << " monedes" << endl;
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

    //Calculamos el movimiento horizontal/vertical de la camara
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
    
    mario_.paint(window);
}
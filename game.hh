#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <set>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "coin.hh"
#include "finder.hh"

class Game {
    std::vector<Coin> coins_;
    int coin_count_ = 0;

    Mario                 mario_;
    std::vector<Platform> platforms_;

    bool finished_, paused_;

    Finder<Platform> platform_finder_;
    Finder<Coin> coin_finder_;

    // Cambiado a punteros constantes para evitar errores de asignación
    std::set<const Platform*> visible_platforms_;
    std::set<const Coin*> visible_coins_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }
     bool is_paused() const {
        return paused_;
    }
 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif

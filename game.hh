#ifndef GAME_HH
#define GAME_HH

#include "mario.hh"
#include "platform.hh"
#include "enemy.hh"
#include "coin.hh"
#include "finder.hh"
#include "window.hh"
#include <vector>
#include <set>

class Game {
 private:
    Mario mario_;
    std::vector<Platform> platforms_;
    std::vector<Enemy> enemies_;
    std::vector<Coin> coins_;

    Finder<Platform> platform_finder_;
    Finder<Coin> coin_finder_;

    std::set<const Platform*> visible_platforms_;
    std::set<const Coin*> visible_coins_;

    bool paused_, finished_, first_update_ = true;

    int lifes;

    int count_coin = 0;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);
    void is_death();

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }
};

#endif

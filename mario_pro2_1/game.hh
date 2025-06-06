#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <set>
#include <list>
#include <stack>

#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "coin.hh"
#include "finder.hh"
#include "enemy.hh"
#include "geometry.hh" 

class Game {
    std::list<Coin> coins_;
    int count_coin = 0;

    Mario mario_;
    pro2::Pt initial_position_;

    std::vector<Platform> platforms_;

    std::stack<int> lives_;

    std::list<Enemy> enemies_;

    Finder<Platform> platform_finder_;
    Finder<Coin> coin_finder_;
    Finder<Enemy> enemy_finder_;

    bool finished_, paused_;

    std::set<const Platform*> visible_platforms_;
    std::set<const Coin*> visible_coins_;
    std::set<const Enemy*> visible_enemies_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);
    void reset_mario();

public:
    Game(int width, int height, int enemy_count);

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

#endif // GAME_HH

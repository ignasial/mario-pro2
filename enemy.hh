#ifndef ENEMY_HH
#define ENEMY_HH

#include "geometry.hh"
#include "window.hh"
#include <vector>

class Enemy {

    pro2::Pt pos_;
    int left_limit_;
    int right_limit_;
    int speed_x_;
    bool alive_;

    static constexpr int Width = 12;
    static constexpr int Height = 10;

    public:
    Enemy(pro2::Pt start_pos, int left_limit, int right_limit);

    void update(pro2::Window& window);

    void paint(pro2::Window& window) const;

    pro2::Rect get_rect() const;

    bool is_alive() const {
        return alive_;
    }
    void kill() {
        alive_ = false;
    }

    private:
        static const std::vector<std::vector<int>> enemy_sprite_;

};



#endif
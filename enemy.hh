// enemy.hh
#ifndef ENEMY_HH
#define ENEMY_HH

#include "geometry.hh"
#include "window.hh"
#include <vector>

class Enemy {
private:
    pro2::Pt pos_;
    pro2::Pt speed_;
    bool alive_ = true;

    int left_limit_;
    int right_limit_;

    static const int Width = 12;
    static const int Height = 16;
    static const std::vector<std::vector<int>> enemy_sprite_;

public:
    Enemy(pro2::Pt pos, int left_limit, int right_limit);

    void update(pro2::Window& window);
    void paint(pro2::Window& window) const;

    bool is_alive() const {
        return alive_;
    }

    pro2::Pt pos() const {
        return pos_;
    }
    pro2::Rect get_rect() const;
};

#endif

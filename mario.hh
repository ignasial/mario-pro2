#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

namespace pro2 {
    struct Pt;
    struct Rect;
    class Window;
}

class Mario {
 private:
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;

    bool grounded_ = false;
    bool looking_left_ = false;

    bool alive_ = true;
    pro2::Pt initial_pos_;  // posición inicial para respawn

    void apply_physics_();

 public:
    Mario(pro2::Pt pos);

    void paint(pro2::Window& window) const;

    pro2::Pt pos() const {
        return pos_;
    }

    void set_y(int y) {
        pos_.y = y;
    }

    bool is_grounded() const {
        return grounded_;
    }

    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    pro2::Rect get_rect() const;

    void jump();

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

    void kill() {
        alive_ = false;
    }

    bool is_alive() const {
        return alive_;
    }

    void respawn() {
        pos_ = {100, 100};
        alive_ = true;
    }

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
};

#endif

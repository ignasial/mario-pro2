// enemy.cc
#include "enemy.hh"
#include "utils.hh"

// Colores
const int _ = -1;      
const int r = pro2::red; 
const int b = pro2::black;  
const int w = pro2::white;  

const std::vector<std::vector<int>> Enemy::enemy_sprite_ = {
   
    {_, _, _, _, _, b, b, b, b, _, _, _, _, _, _, _},
    {_, _, _, _, b, r, r, r, r, b, _, _, _, _, _, _},
    {_, _, _, b, r, r, r, r, r, r, b, _, _, _, _, _},
    {_, _, b, b, b, r, r, r, r, b, b, b, _, _, _, _},
    {_, b, r, w, b, b, b, b, b, b, w, r, b, _, _, _},
    {_, b, r, w, b, w, b, b, w, b, w, r, b, _, _, _},
    {b, r, r, w, w, w, r, r, w, w, w, r, r, b, _, _},
    {b, r, r, r, r, r, r, r, r, r, r, r, r, b, _, _},
    {b, r, r, r, r, r, r, r, r, r, r, r, r, b, _, _},
    {_, b, b, b, b, b, b, b, b, b, b, b, b, _, _, _},
    {b, b, b, b, b, _, _, _, _, b, b, b, b, b, _, _},
    {b, b, b, b, b, _, _, _, _, b, b, b, b, b, _, _},
};



Enemy::Enemy(pro2::Pt pos, int left_limit, int right_limit)
    : pos_(pos), speed_({1, 0}), left_limit_(left_limit), right_limit_(right_limit)
{}

void Enemy::update(pro2::Window& window) {
    pos_.x += speed_.x;

    if (pos_.x < left_limit_) {
        pos_.x = left_limit_;
        speed_.x = -speed_.x;
    } else if (pos_.x > right_limit_) {
        pos_.x = right_limit_;
        speed_.x = -speed_.x;
    }
}

void Enemy::paint(pro2::Window& window) const {
    pro2::Pt top_left = {pos_.x - Width/2, pos_.y - Height};
    paint_sprite(window, top_left, enemy_sprite_, false);
}

pro2::Rect Enemy::get_rect() const {
    return {pos_.x - Width/2, pos_.y - Height, pos_.x + Width/2, pos_.y};
}

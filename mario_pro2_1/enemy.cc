// enemy.cc
#include "enemy.hh"
#include "utils.hh"

// Colores
const int _ = -1;        // transparente
const int r = 0xff0000;  // rojo
const int k = 0x000000;  // negro
const int w = 0xffffff;  // blanco

const std::vector<std::vector<int>> Enemy::enemy_sprite_ = {
    {_, _, _, r, r, r, r, r, _, _, _, _},
    {_, _, r, r, r, r, r, r, r, r, _, _},
    {_, r, r, k, k, r, r, k, k, r, r, _},
    {r, r, k, w, k, r, r, k, w, k, r, r},
    {r, r, k, k, k, k, k, k, k, k, r, r},
    {r, r, r, k, r, r, r, r, k, r, r, r},
    {_, r, r, r, r, r, r, r, r, r, r, _},
    {_, _, r, r, r, r, r, r, r, r, _, _},
    {_, _, _, r, r, r, r, r, r, _, _, _},
    {_, _, _, k, k, k, k, k, k, _, _, _},
    {_, _, k, k, k, k, k, k, k, k, _, _},
    {_, k, k, _, _, _, _, _, _, k, k, _},
    {k, k, _, _, _, _, _, _, _, _, k, k},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, _, _, _},
};

Enemy::Enemy(pro2::Pt pos, int left_limit, int right_limit)
    : pos_(pos), speed_({2, 0}), left_limit_(left_limit), right_limit_(right_limit)
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

#include "enemy.hh"
#include "utils.hh"
using namespace std;

int _ = -1;
int b = pro2::black;
int m = 0x8B4513; // marrón

const vector<vector<int>> Enemy::enemy_sprite_ {
    {_, _, _, _, m, m, m, m, _, _, _, _},
    {_, _, _, m, m, m, m, m, m, _, _, _},
    {_, _, m, m, m, m, m, m, m, m, _, _},
    {_, m, m, b, m, m, m, m, b, m, m, _},
    {m, m, m, m, m, m, m, m, m, m, m, m},
    {m, b, m, m, m, m, m, m, m, b, m, m},
    {m, m, m, m, m, m, m, m, m, m, m, m},
    {_, _, m, m, _, _, _, _, m, m, _, _},
    {_, b, b, b, _, _, _, _, b, b, b, _},
    {b, b, b, b, _, _, _, _, b, b, b, b}
};

Enemy::Enemy(pro2::Pt start_pos, int left_limit, int right_limit)
    : pos_(start_pos), left_limit_(left_limit), right_limit_(right_limit),
      speed_x_(2), alive_(true) {}

void Enemy::update(pro2::Window& window) {
    if (!alive_) return;

    pos_.x += speed_x_;

    if (pos_.x < left_limit_) {
        pos_.x = left_limit_;
        speed_x_ = -speed_x_;
    } else if (pos_.x > right_limit_) {
        pos_.x = right_limit_;
        speed_x_ = -speed_x_;
    }
}

void Enemy::paint(pro2::Window& window) const {
    if (!alive_) return;

    pro2::Pt top_left = {pos_.x - Width / 2, pos_.y - Height};
    pro2::paint_sprite(window, top_left, enemy_sprite_, speed_x_ < 0);
}

pro2::Rect Enemy::get_rect() const {
    return {pos_.x - Width / 2, pos_.y - Height, pos_.x + Width / 2, pos_.y};
}

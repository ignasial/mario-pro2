#include "coin.hh"
#include "utils.hh"
#include <cmath>

using namespace std;
using namespace pro2;

const int _ = -1;
const int y = pro2::yellow;
const int h = pro2::black;

const int amplada  = 11;  
const int altura = 9;  

const int amplitude = 6;
const float frequency = 0.07;

const vector<vector<vector<int>>> Coin::coin_sprites_ = {
{
        {_, _, _, _, _, h, _, _, _, _, _},
        {_, _, _, _, h, y, h, _, _, _, _},
        {_, _, _, h, y, y, y, h, _, _, _},
        {_, _, h, _, y, y, y, _, h, _, _},
        {_, h, y, y, y, y, y, y, y, h, _},
        {_, _, h, _, y, y, y, _, h, _, _},
        {_, _, _, h, y, y, y, h, _, _, _},
        {_, _, _, _, h, y, h, _, _, _, _},
        {_, _, _, _, _, h, _, _, _, _, _},
    },
    {
        {_, _, _, _, _, h, _, _, _, _, _},
        {_, _, _, _, h, y, h, _, _, _, _},
        {_, _, _, h, y, y, y, h, _, _, _},
        {_, _, h, y, _, y, _, y, h, _, _},
        {h, y, y, y, y, y, y, y, y, y, h},
        {_, _, h, y, _, y, _, y, h, _, _},
        {_, _, _, h, y, y, y, h, _, _, _},
        {_, _, _, _, h, y, h, _, _, _, _}, 
        {_, _, _, _, _, h, _, _, _, _, _},
         
    }

};

void Coin::paint(pro2::Window& window) const {
    if (collected_) return;
	
	const Pt top_left = {pos_.x - amplada/2, pos_.y - altura - 1};
    int frame = (window.frame_count() / 10) % coin_sprites_.size();
	vector<vector<int>> actual_sprite = coin_sprites_[frame];
    paint_sprite(window, top_left, actual_sprite, false);
}

void Coin::update(pro2::Window& window) {
    float movement = sin(window.frame_count() * frequency) * amplitude;
    pos_.y = base_pos_.y + movement;
}


// Constructora
Coin::Coin(Pt pos) {
    pos_ = pos;
	base_pos_ = pos;
}


Rect Coin::get_rect() const {
    return {pos_.x-amplada/2, pos_.y-altura, pos_.x+amplada/2, pos_.y};
}

bool Coin::is_collected() const {
	return collected_;
}

void Coin::collect() {
	collected_ = true;
}
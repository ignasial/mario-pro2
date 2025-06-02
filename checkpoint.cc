#include "checkpoint.hh"
#include <cmath>
#include <vector>

const int _ = -1;
const int r = pro2::red;
const int b = pro2::black;

const int Width  = 10;  // ancho del sprite
const int Height = 16;  // alto del sprite

const std::vector<std::vector<int>> checkpoint_sprite = {
    {b, b, r, r, _, _, _, _, _, _},
    {b, b, r, r, r, _, _, _, _, _},
    {b, b, r, r, r, r, _, _, _, _},
    {b, b, r, r, r, r, r, _, _, _},
    {b, b, r, r, r, r, r, r, _, _},
    {b, b, r, r, r, r, r, r, r, _},
    {b, b, r, r, r, r, r, r, r, r},
    {b, b, _, _, _, _, _, _, _, _},
    {b, b, _, _, _, _, _, _, _, _},
    {b, b, _, _, _, _, _, _, _, _},
    {b, b, _, _, _, _, _, _, _, _},
    {b, b, _, _, _, _, _, _, _, _},
    {b, b, _, _, _, _, _, _, _, _},
    {b, b, _, _, _, _, _, _, _, _},
    {b, b, _, _, _, _, _, _, _, _},
    {b, b, _, _, _, _, _, _, _, _},
};


void Checkpoint::insert(Checkpoint* cp) {
    if (cp->x < x) {
        if (left == nullptr) left = cp;
        else left->insert(cp);
    } else {
        if (right == nullptr) right = cp;
        else right->insert(cp);
    }
}

Checkpoint* Checkpoint::find_closest(int px, int py) const {
    Checkpoint* best = nullptr;
    double best_dist = 1e20;

    auto dist = [](int x1, int y1, int x2, int y2) {
        return std::sqrt(double((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
    };

    double current_dist = dist(px, py, x, y);
    if (current_dist < best_dist) {
        best_dist = current_dist;
        best = const_cast<Checkpoint*>(this);
    }

    if (px < x && left != nullptr) {
        Checkpoint* candidate = left->find_closest(px, py);
        if (candidate != nullptr) {
            double d = dist(px, py, candidate->x, candidate->y);
            if (d < best_dist) {
                best_dist = d;
                best = candidate;
            }
        }
    } else if (px >= x && right != nullptr) {
        Checkpoint* candidate = right->find_closest(px, py);
        if (candidate != nullptr) {
            double d = dist(px, py, candidate->x, candidate->y);
            if (d < best_dist) {
                best_dist = d;
                best = candidate;
            }
        }
    }

    return best;
}

void Checkpoint::paint(pro2::Window& window) const {
    for (int dy = 0; dy < Height; ++dy) {
        for (int dx = 0; dx < Width; ++dx) {
            int color = checkpoint_sprite[dy][dx];
            if (color != -1) {
                window.set_pixel({x + dx, y - Height + dy + 1}, (uint32_t)color);
            }
        }
    }

    if (left) left->paint(window);
    if (right) right->paint(window);
}


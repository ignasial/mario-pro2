#ifndef CHECKPOINT_HH
#define CHECKPOINT_HH

#include "window.hh"

struct Checkpoint {
    int x;
    int y;
    Checkpoint* left = nullptr;
    Checkpoint* right = nullptr;

    Checkpoint(int x_, int y_) : x(x_), y(y_) {}

    ~Checkpoint() {
        delete left;
        delete right;
    }

    void insert(Checkpoint* cp);
    Checkpoint* find_closest(int px, int py) const;

    void paint(pro2::Window& window) const;

    // Método añadido para obtener el rectángulo de colisión
    pro2::Rect get_rect() const {
        int half_size = 20;
        return pro2:: Rect{
            x - half_size,
            y - half_size,
            x + half_size,
            y + half_size
        };
    }
};

#endif
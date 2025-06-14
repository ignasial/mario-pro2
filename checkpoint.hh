#ifndef CHECKPOINT_HH
#define CHECKPOINT_HH

#include "window.hh"

/**
 * @brief struct encargado de gestionar los puntos de control del juego
 */
struct Checkpoint {
    int x;
    int y;
    Checkpoint* left = NULL;
    Checkpoint* right = NULL;

    Checkpoint(int x_, int y_) : x(x_), y(y_) {}

    ~Checkpoint() {
        delete left;
        delete right;
    }

    /**
     * @brief inserta un punto de control en el arbol
     * @param cp punto de control tipo checkpoint
     */
    void insert(Checkpoint* cp);
    /**
     * @brief encuentra el punto de control mas cercano a un punto
     * @param px, py dos enteros representando componentes de un punto (px, py)
     */
    Checkpoint* find_closest(int px, int py) const;

    /**
     * @brief pinta el sprite de la banderita representando el checkpoint
     * @param window del namespace pro2
     */
    void paint(pro2::Window& window) const;

    /**
     * @brief devuelve el rectangulo que ocupa la banderita representando el checkpoint
     */
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
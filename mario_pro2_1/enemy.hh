// enemy.hh
#ifndef ENEMY_HH
#define ENEMY_HH

#include "geometry.hh"
#include "window.hh"
#include <vector>


/**
 * @brief clase que representa a los enemigos del juego
 */
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

    /**
     * @brief actualiza la posicion del enemigo con un movimiento horizontal
     * @param 
     */
    void update(pro2::Window& window);
      /**
     * @brief pinta el sprite del enemigo
     */
    void paint(pro2::Window& window) const;
      /**
     * @brief 
     */
    bool is_alive() const {
        return alive_;
    }
      /**
     * @brief
     */
    pro2::Pt pos() const {
        return pos_;
    }
      /**
     * @brief
     */
    pro2::Rect get_rect() const;
};

#endif

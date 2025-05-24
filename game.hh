#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <set>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "coin.hh"
#include "finder.hh"

/**
 * @brief Clase que gestiona el funcionamiento del juego.
 */
class Game {
    std::vector<Coin> coins_;
    int count_coin = 0;

    Mario mario_;
    std::vector<Platform> platforms_;

    bool finished_, paused_;

    Finder<Platform> platform_finder_;
    Finder<Coin> coin_finder_;

    std::set<const Platform*> visible_platforms_;
    std::set<const Coin*> visible_coins_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

public:
    /**
     * @brief Constructora que inicializa el juego con el tamaño de ventana dado.
     * @param width Anchura de la ventana del juego.
     * @param height Altura de la ventana del juego.
     */
    Game(int width, int height);

    /**
     * @brief Actualiza el estado general del juego.
     */
    void update(pro2::Window& window);

    /**
     * @brief Dibuja el juego en la ventana.
     */
    void paint(pro2::Window& window);

    /**
     * @brief Indica si el juego ha finalizado.
     */
    bool is_finished() const {
        return finished_;
    }

    /**
     * @brief Indica si el juego está pausado.
     */
    bool is_paused() const {
        return paused_;
    }

private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif

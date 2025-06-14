#ifndef GAME_HH
#define GAME_HH

#include "mario.hh"
#include "platform.hh"
#include "coin.hh"
#include "enemy.hh"
#include "checkpoint.hh"
#include "finder.hh"
#include "message.hh"
#include <list>
#include <stack>
#include <set>



class Game {
public:
    Game(int width, int height, int enemy_count);
    ~Game();

    /**
     * @brief procesa las teclas de entrada del juego
     */
    void process_keys(pro2::Window& window);
    /**
     * @brief actualiza el estado del juego
     */
    void update(pro2::Window& window);
      /**
     * @brief pinta los objetos del juego
     */
    void paint(pro2::Window& window);

      /**
     * @brief recoloca el mario en el mapa
     */
    void reset_mario(pro2::Window& window);

    /**
     * @brief devuelve el valor de la variable finished_
     */
    bool is_finished() const {
        return finished_;
    }

    std::list<Enemy>& enemies();
    std::list<Coin>& coins();
    Finder<Enemy>& enemy_finder();
    Finder<Coin>& coin_finder();

private:
      /**
     * @brief añade un checkpoint al juego
     * @param x, y coordenadass del punto donde se quiere añadir el checkpoint
     */
    void add_checkpoint(int x, int y);
      /**
     * @brief actualiza los objetos del juego
     */
    void update_objects(pro2::Window& window);
    /**
     * @brief actualiza la camara de enfoque del juego
     */
    void update_camera(pro2::Window& window);

    Mario mario_;
    std::vector<Platform> platforms_;
    std::list<Coin> coins_;
    std::list<Enemy> enemies_;

    Finder<Platform> platform_finder_;
    Finder<Coin> coin_finder_;
    Finder<Enemy> enemy_finder_;

    std::set<const Platform*> visible_platforms_;
    std::set<Coin*> visible_coins_;
    std::set<Enemy*> visible_enemies_;

    bool paused_;
    bool finished_;

    std::stack<int> lives_;
    int count_coin;

    Checkpoint* root_checkpoint_;
    Checkpoint* current_checkpoint_;

    pro2::Pt initial_position_;

    MessageQueue message_queue_;
    
    int current_frame_;
    static constexpr int sky_blue = 0x5c94fc;
};

 
#endif // namespace pro2

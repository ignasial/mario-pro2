#ifndef COIN_HH
#define COIN_HH

#include <iostream>
#include <vector>
#include <cmath>
#include "window.hh"


/**
 * @brief Clase que representa una moneda y sus acciones dentro del juego.
 */
class Coin {
    private:
        pro2::Pt base_pos_;
        pro2::Pt pos_;
        bool collected_ = false;
        bool message_shown_ = false; 
        static const std::vector<std::vector<std::vector<int>>> coin_sprites_;


    public:
        //Constructora:
        /**
         * @brief Constructora que inicializa la moneda en una posición dada.
         * @param pos Posición inicial de la moneda.
         */
        Coin(pro2::Pt pos);


        //Consultoras:
        /**
         * @brief Devuelve el rectángulo que ocupa la moneda (para colisiones, dibujo, etc.).
         */
        pro2::Rect get_rect() const;

        /**
         * @brief Indica si la moneda ha sido recogida.
         */
        bool is_collected() const;

         /**
         * @brief inicializa la variable message_shown_ a un valor dado
         * @param value un valor booleano
         */
        void set_message_shown(bool value) {
            message_shown_ = value; 
        }

        /**
         * @brief devuelve el valor de la variable message_shown_
         */
        bool message_shown() const {
            return message_shown_; 
        }


        //Modificadoras:
        /**
         * @brief Marca la moneda como recogida.
         */
        void collect();

        /**
         * @brief Dibuja la moneda en la ventana.
         * @param un window de pro2
         */
        void paint(pro2::Window& window) const;   

        /**
         * @brief Actualiza el estado de la moneda (por ejemplo, animaciones).
         * @param un window de pro2
         */
        void update(pro2::Window& window);

       

};

#endif

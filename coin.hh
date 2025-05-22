#ifndef COIN_HH
#define COIN_HH

#include <iostream>
#include <vector>
#include <cmath>
#include "window.hh"

class Coin {
    private:
        pro2::Pt base_pos_;
        pro2::Pt pos_;
        bool collected_ = false;

    public:
        // Constructora
        Coin(pro2::Pt pos);
        // Consultores
        pro2::Pt getPos();
        pro2::Rect get_rect() const;

        bool is_collected() const;

        // Modificadores
        void collect();
        void paint(pro2::Window& window) const;
        void update(pro2::Window& window);

    private:
        static const std::vector<std::vector<std::vector<int>>> coin_sprites_;

};

#endif
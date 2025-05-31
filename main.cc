#include <iostream>
#include <vector>
#include "game.hh"
#include "window.hh"

using namespace std;

const int WIDTH = 480, HEIGHT = 320;
const int ZOOM = 2;
const int FPS = 48;

int main() {
    cout << "¿Cuántos enemigos quieres al empezar el juego? ";
    int enemy_count;
    cin >> enemy_count;
    if (enemy_count < 0) enemy_count = 0; 

    pro2::Window window("Mario Pro 2", WIDTH, HEIGHT, ZOOM);
    window.set_fps(FPS);

    Game game(WIDTH, HEIGHT, enemy_count);

    while (window.next_frame() && !game.is_finished()) {
        game.update(window);
        game.paint(window);
    }
}

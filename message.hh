#ifndef MESSAGE_HH
#define MESSAGE_HH

#include <queue>
#include <string>
#include "window.hh"


/**
 * @brief clase que usa una queue para gestionar la salida de informacion por terminal
 */
class MessageQueue {
public:

    /**
     * @brief carga el mensaje que queremos imprimir
     * @param msg el mensaje que se desea imprimir en un momento determinado
     */
    void push(const std::string& msg, int frames = 120); 
    /**
     * @brief encargado de cargar y eliminar mensajes de la cola
     */
    void update();

private:
    std::queue<std::pair<std::string, int>> messages_;

};



#endif 
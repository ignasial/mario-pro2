#ifndef MESSAGE_QUEUE_HH
#define MESSAGE_QUEUE_HH

#include <queue>
#include <string>
#include "window.hh"

class MessageQueue {
public:
    void push(const std::string& msg, int frames = 120); //2s a 60 fps
    void update();

private:
    std::queue<std::pair<std::string, int>> messages_;

};



#endif 
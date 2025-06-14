#include "message.hh"
#include <iostream>

void MessageQueue::push(const std::string& msg, int frame) {
    messages_.push({msg, frame});

    std::cout << msg << std::endl;
}

void MessageQueue::update() {
    if (messages_.empty()) return;

    auto& front = messages_.front();
    if (--front.second <= 0) {
        messages_.pop();
    }
}


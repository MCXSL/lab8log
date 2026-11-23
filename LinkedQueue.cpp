#include "LinkedQueue.h"
#include <stdexcept>

LinkedQueue::LinkedQueue() : first(nullptr), last(nullptr) {}

LinkedQueue::~LinkedQueue() {
    while (!empty()) {
        pop();
    }
}

bool LinkedQueue::empty() const {
    return first == nullptr;
}

void LinkedQueue::push(int value) {
    Node* node = new Node{value, nullptr};
    if (empty()) {
        first = node;
    } else {
        last->next = node;
    }
    last = node;
}

int LinkedQueue::front() const {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    return first->value;
}

void LinkedQueue::pop() {
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    }
    Node* old = first;
    first = first->next;
    delete old;
    if (first == nullptr) {
        last = nullptr;
    }
}

#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

// Очередь на односвязном списке: добавляем в конец, удаляем из начала.
class LinkedQueue {
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* first;
    Node* last;

public:
    LinkedQueue();
    ~LinkedQueue();
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    bool empty() const;
    void push(int value);
    int front() const;
    void pop();
};

#endif

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "Node.h"

template<typename K, typename V>
class DoublyLinkedList {
    private:
        Node<K,V>* head, *tail;
    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr) {}

        void add(Node<K,V>* node);          // Add node to the front (most recently used)
        void update(Node<K,V>* node);       // Move existing node to the front
        K removeLast();                     // Remove and return key of least recently used node (tail)
};

#endif
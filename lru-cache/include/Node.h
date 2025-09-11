#ifndef NODE_H
#define NODE_H

template<typename K, typename V>
class Node {
    public:
        K key;
        V value;
        Node<K, V>* prev, *next;
        Node(K key, V value) : key(key), value(value), prev(nullptr), next(nullptr) {}
};

#endif
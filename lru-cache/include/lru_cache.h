#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <map>
#include <mutex>

#include "node.h"
#include "doublyLinkedList.h"

template<typename K, typename V>
class LRUCache {
    private:
        int capacity, size;
        DoublyLinkedList<K,V> history;
        std::map<K, Node<K,V>*> hashMap;
        std::mutex cacheMutex;

        void evict();                        // Remove least recently used entry if over capacity

    public:
        LRUCache(int capacity) : capacity(capacity), size(0) {}

        V get(K key);                      // Retrieve value if key exists, else null
        void put(K key, V value);           // Insert or update key-value pair
};

#endif
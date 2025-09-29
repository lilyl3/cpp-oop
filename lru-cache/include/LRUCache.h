#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <map>
#include <mutex>
#include <stdexcept>
#include <type_traits>
#include <iostream>

using namespace std;

#include "Node.h"
#include "DoublyLinkedList.h"

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
        ~LRUCache();

        V* get(K key);                      // Retrieve pointer to value if key exists, else null
        void put(K key, V value);           // Insert or update key-value pair
};

// Note: Templates are instantiated @ compile time
template<typename K, typename V>
LRUCache<K,V>::~LRUCache<K,V>(){
    for (auto& pair : hashMap) {
        delete pair.second; // deallocate
    }
    hashMap.clear();
}

template<typename K, typename V>
V* LRUCache<K,V>::get(K key) {
    lock_guard<mutex> lock(cacheMutex);

    auto it = hashMap.find(key);
    if (it == hashMap.end()) {
        // constexpr evaluates expression @ compile time, not run time
        // chooses which branch to compile
        if constexpr (is_same_v<V, string>) {
            return nullptr;
        } else if constexpr (is_same_v<V, int> || is_same_v<V, double>){
            return nullptr;
        } else {
            throw invalid_argument("Unsupported type.");
        }
    }
    // cout << "cache get key: " << key << ", value: " << it->second->value << endl;
    // update most recently used
    history.update(it->second);
    return &it->second->value;
}

// Remove least recently used entry
// Only called when overcapacity
template<typename K, typename V>
void LRUCache<K,V>::evict() {
    Node<K,V>* lruNode = history.removeLast();
    // cout << "Removed key " << lruNode->key << " from the cache." << endl;
    hashMap.erase(lruNode->key);
    delete lruNode;
}

// Insert or update key-value pair
template<typename K, typename V>
void LRUCache<K,V>::put(K key, V value) {
    lock_guard<mutex> lock(cacheMutex);

    // cout << "cache put key: " << key << ", value: " << value << endl;

    auto it = hashMap.find(key);
    if (it != hashMap.end()){
        // update existing cache entry
        it->second->value = value;
        history.update(it->second);
    } else {
        // insert new cache entry
        // if overcapacity, evict
        if (size < capacity) size++;
        else evict();

        Node<K,V>* nodePtr = new Node<K,V>(key, value);
        history.add(nodePtr);
        hashMap[key] = nodePtr;
    }
}      

#endif
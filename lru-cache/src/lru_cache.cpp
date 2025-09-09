#include "node.h"
#include "doublyLinkedList.h"
#include "lru_cache.h"

#include <stdexcept>
#include <mutex>
#include <type_traits>

using namespace std;

// templates are instantiated @ compile time
template<typename K, typename V>
V LRUCache<K,V>::get(K key) {
    lock_guard<mutex> lock(cacheMutex);

    auto it = hashMap.find(key);
    
    if (it == hashMap.end()) {
        // constexpr evaluates expression @ compile time, not run time
        // chooses which branch to compile
        if constexpr (is_same_v<V, string>) {
            return "";
        } else if constexpr (is_same_v<V, int> || is_same_v<V, double>){
            return static_cast<V>(-1);
        } else {
            throw invalid_argument("Unsupported type.");
        }
    }
    // update most recently used
    history.update(it->second);
    return it->second->value;
}

// Remove least recently used entry
// Only called when overcapacity
template<typename K, typename V>
void LRUCache<K,V>::evict() {
    Node<K,V>* lruNode = history.removeLast();
    hashMap.erase(lruNode->key);
    delete lruNode;
}

// Insert or update key-value pair
template<typename K, typename V>
void LRUCache<K,V>::put(K key, V value) {
    lock_guard<mutex> lock(cacheMutex);

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
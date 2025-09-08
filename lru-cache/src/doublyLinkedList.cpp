#include "node.h"
#include "doublyLinkedList.h"

#include <stdexcept>

using namespace std;

template<typename K, typename V>
void DoublyLinkedList<K,V>::add(Node<K,V>* node){
    node->prev = nullptr;
    if (head) {
        node->next = head;
        head->prev = node;
        head = node;
    } else {
        // adding first cache entry
        node->next = nullptr;
        head = node;
        tail = node;
    }
}

template<typename K, typename V>
void DoublyLinkedList<K,V>::update(Node<K,V>* node) {
    if (node == head) return;
    else if (node == tail) {
        // node is NOT the head ==> there exists another node in the list
        tail = node->prev;
        tail->next = nullptr;
    } else {
        // node is NOT the head or tail, so node->prev and node->next can NOT be null
        (node->prev)->next = node->next;
        (node->next)->prev = node->prev;
    }

    add(node);
}

template<typename K, typename V>
K DoublyLinkedList<K,V>::removeLast() {
    if (!tail) throw logic_error("The list is empty.");
    // check if cache entry is the tail (i.e. least recently used)
    if (tail->next) throw logic_error("The 'tail' is not the tail of the list.");

    K key = tail->key;
    if (head == tail) {
        // removing single cache entry
        head = nullptr;
        tail = nullptr;
    } else {
        // more than 1 cache entry in the list
        if (!tail->prev) throw logic_error("Cache should contain >= 2 entries, but tail->prev is null.");
        // reset tail
        tail = tail->prev;
        tail->next = nullptr;
    }
    return key;
}
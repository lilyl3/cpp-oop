# LRU Cache
This project implements a simple LRU cache that stores key-value pairs the supports fast access and eviction of the least recently used items.

## Clarifying Requirements
1. What kind of data is stored in the cache?
- The cache should support any type. Keys are assumed to be hashable.
2. What operations does the cache support besides ```get, put```?
- Assume ```get, put``` are the only operations supported by the cache.
3. What if a key does not exist? 
- Return ```null```.
4. Should a ```put``` be considered as usage of a key?
- An update to an *existing* key via ```put``` is considered usage. That key is now most recently used.
5. Is the cache used in a multi-threaded environment?
- Yes, so it should be thread-safe.
6. Are there any performance requirements for ```get, put```?
- Both should run on average O(1).


## Design
- A cache requires fast lookup (e.g., ```map```) and fast ordering (```doubly linked list```). 

1. Node
– Represents a single entry in the cache with pointers to previous and next nodes for list traversal.
```cpp
int key
auto value
Node* prev, next

void set(auto newValue)     // Update value of the node
auto get()                  // Return current value
```

2. DoublyLinkedList
```cpp
Node* head, tail

void add(Node* node)        // Add node to the front (most recently used)
void update(Node* node)     // Move existing node to the front
int removeLast()            // Remove and return key of least recently used node (tail)
```

3. LRUCache
```cpp
int capacity, size
DoublyLinkedList history
map<int, Node*> HashMap

auto get(int key)                   // Retrieve value if key exists, else null
void put(int key, auto value)       // Insert or update key-value pair
void evict()                        // Remove least recently used entry if over capacity
```
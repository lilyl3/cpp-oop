# Bloom Filter

A **Bloom filter** is a **probabilistic data structure** used to efficiently test whether an element is a member of a set. It is space-efficient and allows for fast membership checks with a small risk of **false positives**, but **never false negatives**.

---

## 📐 Structure

A Bloom filter consists of:

1. A **bit array** of size `m`, initially set to all `0`s.
2. `k` **independent hash functions**, each of which maps an input `element` to one of the `m` bit positions.

---

## ⚙️ Operations

A Bloom filter supports the following operations:

1. #### `add(element)`

- Compute `k` hash values for the given `element`.
- For each hash value, set the corresponding bit in the array to `1`.

2. #### `mightContain(element)`

- Compute `k` hash values for the `element`.
- Check the bits at the corresponding positions:
  - If **any** bit is `0`, return **`false`** → the element is **definitely not** in the set.
  - If **all** bits are `1`, return **`true`** → the element is **possibly** in the set (could be a false positive).

---

## ✅ Requirements

1. The values of `k` (number of hash functions) and `m` (bit array size) must be **configurable**.
2. The Bloom filter must support **concurrent access** in a **multi-threaded environment**.

## Design
Bloom filter should support generic types but initially assume `int`.

1. BitArray
```cpp
int size;
bool* bits; // dynamically allocate => returns a pointer

void setBits(vector<int> positions);
bool areAllBitsSet(vector<int> positions);
```

2. HashFunction
```cpp
// Abstract
int m;
virtual int hash(int element) = 0;
```

3. BloomFilter
```cpp
BitArray bitArray;
// HashFunction is a abstract class
vector<HashFunction*> hashFunctions;

void addElement(int element)
bool mightContain(int element);
```

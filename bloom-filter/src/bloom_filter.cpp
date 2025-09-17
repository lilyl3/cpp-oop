#include <vector>

#include "bloom_lib.h"

using namespace std;

BloomFilter::BloomFilter(int m, int k, const vector<HashFunction*>& hashFunctions)
    : bitArray(m), k(k), hashFunctions(hashFunctions) {
}

// Helper function to compute all k hash values of the given element
void BloomFilter::computeHash(vector<int>& positions, int element) {
    positions.clear();  // reset before computing
    for (HashFunction* hashPtr : hashFunctions) {
        positions.push_back(hashPtr->hash(element));
    }
}

// Adds an element to the Bloom filter by setting bits corresponding to hash positions
void BloomFilter::addElement(int element) {
    vector<int> positions;
    computeHash(positions, element);
    bitArray.setBits(positions);
}

// Checks if an element might be in the Bloom filter
// Returns false if any bit at the hash positions is 0 (element definitely not in set)
// Returns true if all bits are set (element possibly in set, with som
bool BloomFilter::mightContain(int element) {
    vector<int> positions;
    computeHash(positions, element);
    return bitArray.areAllBitsSet(positions);
}

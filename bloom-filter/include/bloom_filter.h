#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include "bit_array.h"
#include "hash_function.h"

class BloomFilter {
    private:
        BitArray bitArray;
        std::vector<HashFunction*> hashFunctions;

        void computeHash(std::vector<int>&, int);
    public:
        BloomFilter(int, const std::vector<HashFunction*>&);
        void addElement(int);
        bool mightContain(int);
};

#endif
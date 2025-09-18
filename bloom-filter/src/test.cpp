#include <cassert>
#include <functional>

#include "bloom_lib.h"
#include "test.h"

using namespace std;

void Test::test1(){
    int m = 12;
    // initialize HashFunctions
    ModularHash modularHash(m);
    MultiplicativeHash multiplicativeHash(m, 3, 4);

    // vector of pointers to hash functions
    vector<HashFunction*> hashFunctions = { &modularHash, &multiplicativeHash };

    // add element and assert membership
    BloomFilter bloomFilter(m, hashFunctions);
    bloomFilter.addElement(6);  // hashes to 6, 10
    assert(bloomFilter.mightContain(6));
    bloomFilter.addElement(96); // hashes to 0, 4
    assert(bloomFilter.mightContain(96));
    bloomFilter.addElement(25); // hashes to 1, 7
    assert(bloomFilter.mightContain(25));

    // test non-membership
    assert(!bloomFilter.mightContain(17));   // hashes to 5, 7
    // test false positive
    assert(bloomFilter.mightContain(18));   // hashes to 6, 10
}
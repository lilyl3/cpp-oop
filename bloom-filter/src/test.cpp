#include <cassert>
#include <functional>
#include <pthread.h>
#include <chrono>
#include <thread>
#include <random>
#include <iostream>

#include "bloom_lib.h"
#include "test.h"

using namespace std;

void Test::test1() {
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

// Returns all elements in [0, max] whose hash values fall within validPositions for all given hash functions.
void Test::findElementsMatchingHashes(
    int max, const set<int>& validPositions, const vector<HashFunction*>& hashFunctions, 
    vector<int>& members, vector<int>& nonMembers
) {
    int k = hashFunctions.size();
    for (int i = 0; i <= max; i++) {
        int count = 0;
        for (HashFunction* hashFunctionPtr : hashFunctions) {
            int pos = hashFunctionPtr->hash(i);
            if (validPositions.find(pos) != validPositions.end()) {
                count++;
            }
        }
        if (count == k) members.push_back(i);
        else nonMembers.push_back(i);
    }
}

struct ThreadArgs {
    BloomFilter& bloomFilter;
    const vector<int>* elementPool;
};

void* bloom_filter_thread(void* args) {
    ThreadArgs* threadArgs = static_cast<ThreadArgs*>(args);
    BloomFilter& bloomFilter = threadArgs->bloomFilter;
    const vector<int>* elementPool = threadArgs->elementPool;

    random_device rd;    
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, elementPool->size() - 1);

    for (int i = 0; i < 10; i++){
        // add random element from pool into bloom filter
        int element = (*elementPool)[dist(gen)];
        bloomFilter.addElement(element);
        this_thread::sleep_for(chrono::milliseconds(25));
        // assert membership
        assert(bloomFilter.mightContain(element));
        this_thread::sleep_for(chrono::milliseconds(15));
    }

    return nullptr;
}

void Test::test2() {
    int m = 12;
    // initialize HashFunctions
    ModularHash modularHash(m);
    MultiplicativeHash multiplicativeHash(m, 3, 4);

    // vector of pointers to hash functions
    vector<HashFunction*> hashFunctions = { &modularHash, &multiplicativeHash };

    // find set of integers between [0, 250] whose hash values ALL fall within validPositions
    set<int> validPositions = {0, 1, 4, 5, 6, 7, 10};
    vector<int> memberPool, nonMembersPool;
    findElementsMatchingHashes(250, validPositions, hashFunctions, memberPool, nonMembersPool);

    BloomFilter bloomFilter(m, hashFunctions);

    // create 3 threads that randomly add elements from the "valid" pool of elements
    pthread_t thread1, thread2, thread3;
    ThreadArgs* args = new ThreadArgs{bloomFilter, &memberPool};
    pthread_create(&thread1, NULL, bloom_filter_thread, args);
    pthread_create(&thread2, NULL, bloom_filter_thread, args);
    pthread_create(&thread3, NULL, bloom_filter_thread, args);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    assert(nonMembersPool.size() != 0);
    // assert that Bloom filter returns false for non-members
    for (int nonMember : nonMembersPool){
        assert(!bloomFilter.mightContain(nonMember));
    }

    delete args;    // deallocate
}
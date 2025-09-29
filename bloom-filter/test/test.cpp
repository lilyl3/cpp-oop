#include <gtest/gtest.h>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

#include "bloom_lib.h"

using namespace std;

class BloomFilterTest : public testing::Test {
protected:
    static constexpr int m = 12;

    ModularHash modularHash;
    MultiplicativeHash multiplicativeHash;
    vector<HashFunction*> hashFunctions;
    BloomFilter bloomFilter;

    BloomFilterTest()
        : modularHash(m),
          multiplicativeHash(m, 3, 4),
          hashFunctions{&modularHash, &multiplicativeHash},
          bloomFilter(m, hashFunctions)
    {}
};

// Verify that added elements are reported as present
TEST_F(BloomFilterTest, DetectsInsertedElements){
    bloomFilter.addElement(96);                     // hashes to 0, 4
    EXPECT_TRUE(bloomFilter.mightContain(96));
    bloomFilter.addElement(25);                     // hashes to 1, 7
    EXPECT_TRUE(bloomFilter.mightContain(25));
}

// Confirm that a non-inserted element is reported as absent
TEST_F(BloomFilterTest, RejectsUnseenElement){
    EXPECT_FALSE(bloomFilter.mightContain(17));     // hashes to 5, 7
}

// Demonstrate a false positive: element not added but bits are set
TEST_F(BloomFilterTest, MayHaveFalsePositives){
    EXPECT_FALSE(bloomFilter.mightContain(10));     // hashes to 10
    bloomFilter.addElement(6);                      // hashes to 6, 10
    EXPECT_TRUE(bloomFilter.mightContain(6));
    EXPECT_TRUE(bloomFilter.mightContain(18));      // hashes to 6, 10
}

void setElementPool(
    const set<int>& hashPool, 
    vector<int>& elementPool,
    const int n, 
    const vector<HashFunction*>& hashFunctions 
) {
    for (int i = 0; i < n; i++){
        bool inPool = true;
        for (HashFunction* hfPtr : hashFunctions){
            if (hashPool.find(hfPtr->hash(i)) == hashPool.end()) inPool = false;
        }
        if (inPool) elementPool.push_back(i);
    }
}

void addWorker(const vector<int> elementPool, BloomFilter* bloomFilter) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, elementPool.size() - 1); // inclusive

    for(int i = 0; i < 300; i++){
        bloomFilter->addElement(elementPool[dist(gen)]);
        this_thread::sleep_for(chrono::milliseconds(dist(gen) % 30));
    } 
}

TEST_F(BloomFilterTest, Multithread) {
    const int n = 250;
    set<int> hashPool = {0, 1, 4, 5, 6, 7, 10};
    vector<int> elementPool = {};
    setElementPool(hashPool, elementPool, n, hashFunctions);
    ASSERT_GT(elementPool.size(), static_cast<size_t>(0));

    const int numWorkers = 10;
    vector<thread> workers;

    for(int i = 0; i < numWorkers; i++){
        workers.emplace_back(addWorker, elementPool, &bloomFilter);
    }

    for(int i = 0; i < numWorkers; i++){
        workers[i].join();
    }

    for (int i = 0; i < n; i++){
        if (find(elementPool.begin(), elementPool.end(), i) == elementPool.end()) {
            EXPECT_FALSE(bloomFilter.mightContain(i));
        }
    }
}
#include <gtest/gtest.h>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <future>

#include "lru_cache.h"

using namespace std;

class SingleThreadTest : public testing::Test {
 protected:
  SingleThreadTest() : c0(10), c1(16){
    c1.put(13, 3);
    c1.put(7, 5);
  }

  LRUCache<string, int> c0;
  LRUCache<int, int> c1;
};

TEST_F(SingleThreadTest, SimpleGetPut) {
  // Cache initially empty
  int* ptr = c0.get("alice");
  EXPECT_EQ(ptr, nullptr);

  c0.put("bob", 5);
  ptr = c0.get("bob");
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 5);
}

TEST_F(SingleThreadTest, Eviction) {
  int* ptr = c1.get(13);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 3);

  ptr = c1.get(7);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 5);

  // Fill cache to capacity
  for (int i = 0; i < 14; i++){
    c1.put(2*i, i);
    ptr = c1.get(2*i);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, i);
  }

  // Cache should not be overcapacity
  ptr = c1.get(13);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 3);

  c1.put(1, 19);
  ptr = c1.get(1);
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(*ptr, 19);

  // Key 7 should be evicted because overcapacity
  ptr = c1.get(7);
  EXPECT_EQ(ptr, nullptr);
}

// Worker thread: inserts and checks keys in a unique range.
// Reports success/failure via promise.
void disjointWorker(int id, int keyPartitionSize, LRUCache<int, int>* cachePtr, promise<bool> p){
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> iDist(0, keyPartitionSize - 1);
  uniform_int_distribution<> tDist(5, 20);

  int baseKey = keyPartitionSize * id, key, value, *ptr = nullptr;
  bool isCorrect = true;

  for (int i = 0; i < keyPartitionSize * 6; i++){
      // Randomly generate a key, value pair to add to the cache
      key = baseKey + iDist(gen);
      value = key + tDist(gen);
      cachePtr->put(key, value);

      this_thread::sleep_for(chrono::milliseconds(tDist(gen)));

      ptr = cachePtr->get(key);
      if(ptr == nullptr || *ptr != value){
        isCorrect = false;
      }

      this_thread::sleep_for(chrono::milliseconds(tDist(gen)));
  }
  p.set_value(isCorrect);
}

// Launches threads that work on disjoint key ranges in the cache.
// Verifies all threads complete without errors.
TEST(MultithreadTest, DisjointPuts) {
  const int nThreads = 10, keyPartitionSize = 50;
  LRUCache<int, int> cache(keyPartitionSize * nThreads);

  thread threads[nThreads];
  future<bool> futures[nThreads];

  // Launch threads
  for (int i = 0; i < nThreads; i++){
    // promise ==> start of a pipe
    // future  ==> end of a pipe
    promise<bool> p;
    futures[i] = p.get_future();
    threads[i] = thread(disjointWorker, i, keyPartitionSize, &cache, std::move(p));
  }

  for (int i = 0; i < nThreads; i++){
    threads[i].join();
    EXPECT_TRUE(futures[i].get()) << "Worker " << i << " failed";
  }
}

// All threads insert the same keys [0, n), but with different values (their thread ID).
// Insertion happens incrementally with some delay to simulate concurrency.
void putWorker(int id, int n, LRUCache<int, int>* cachePtr){
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> tDist(5, 25);

  for (int i = 0; i < n; i++){
      cachePtr->put(i, id);
      this_thread::sleep_for(chrono::milliseconds(tDist(gen)));
  }
}

TEST(MultithreadTest, Eviction) {
  const int numWorkers = 10;        // Number of concurrent threads
  const int n = 120;                // Each thread inserts n keys (same keys [0, n))
  const int size = 100;             // LRU cache capacity

  ASSERT_GT(n, size);               // Ensure some keys will be evicted
  
  LRUCache<int, int> cache(size);
  vector<thread> workers;

  for (int i = 0; i < numWorkers; i++){
    workers.emplace_back(putWorker, i, n, &cache);
  }

  for (int i = 0; i < numWorkers; i++){
    workers[i].join();
  }

  // Since all threads inserted the same key range [0, n),
  // and the keys were inserted in increasing order,
  // the LRU policy should evict the earliest keys (from 0 to n - size - 1).
  for (int i = 0; i < n; i++){
    if (i < n - size) EXPECT_EQ(cache.get(i), nullptr);
    else EXPECT_NE(cache.get(i), nullptr);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
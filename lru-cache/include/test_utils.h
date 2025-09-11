#ifndef TEST_H
#define TEST_H

#include "node.h"
#include "doublyLinkedList.h"
#include "lru_cache.h"

#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

class TestUtils{
    private:
        random_device rd;    
        mt19937 gen;
        uniform_int_distribution<> dist;
        mutex mtx;

    public:
        TestUtils() : gen(rd()), dist(1, 10) {}

        int getRandom() {
            lock_guard<mutex> lock(mtx);
            return dist(gen);
        }

        // test simple get and put
        void singleThread_test1(){
            LRUCache<string, int> lruCache = LRUCache<string, int>(10);
            assert(lruCache.get("alice") == -1);
            lruCache.put("alice", 1);
            assert(lruCache.get("alice") == 1);
        }

        // test eviction + update
        void singleThread_test2(){
            LRUCache<string, string> lruCache = LRUCache<string, string>(5);
            // empty cache
            assert(lruCache.get("alice") == "");

            // fill cache
            lruCache.put("alice", "bob");
            lruCache.put("bob", "cathy");
            lruCache.put("cathy", "daniel");
            lruCache.put("daniel", "elizabeth");
            lruCache.put("elizabeth", "fiona");  
            // cache is full
            assert(lruCache.get("alice") == "bob");

            lruCache.put("fiona", "george");
            // cache should evict "bob" because we requested "alice"
            assert(lruCache.get("bob") == "");
            assert(lruCache.get("fiona") == "george");

            // add "bob" back into the cache
            lruCache.put("bob", "cathy");
            // cache is still full, so "cathy" should be evicted
            assert(lruCache.get("cathy") == "");

            // update; no eviction
            lruCache.put("daniel", "emory");
            assert(lruCache.get("daniel") == "emory");
        }

        // static shared by all instances of the class; no access to the this pointer
        static void* oddWorker(void* arg){
            LRUCache<int, int>* cachePtr = static_cast<LRUCache<int, int>*>(arg);
            for (int i = 0; i < 5; i++){
                cachePtr->put(i, 2*i+1);
                this_thread::sleep_for(chrono::milliseconds(40));
                cachePtr->get(i);
                // pause execution => CPU idle => context switching
                this_thread::sleep_for(chrono::milliseconds(25));
            }
            return nullptr;
        }

        static void* evenWorker(void* arg){
            LRUCache<int, int>* cachePtr = static_cast<LRUCache<int, int>*>(arg);
            for (int i = 0; i < 5; i++){
                cachePtr->put(i, 2*i);
                this_thread::sleep_for(chrono::milliseconds(35));
                cachePtr->get(i);
                this_thread::sleep_for(chrono::milliseconds(15));
            }
            return nullptr;
        }

        // test multiple threads accessing cache
        void multiThread_test1(){
            LRUCache<int, int> lruCache = LRUCache<int, int>(3);
            pthread_t oddThread, evenThread;

            int rc1 = pthread_create(&oddThread, NULL, oddWorker, &lruCache);
            int rc2 = pthread_create(&evenThread, NULL, evenWorker, &lruCache);
            if (rc1 || rc2) {
                printf("Error creating thread: %d, %d\n", rc1, rc2);
                return;
            }

            // Wait for thread to finish
            pthread_join(oddThread, NULL);
            pthread_join(evenThread, NULL);
        }
};

#endif
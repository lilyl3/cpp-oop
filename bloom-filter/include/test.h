#ifndef TEST_H
#define TEST_H

#include <vector>
#include <set>

class Test {
    public:
        void test1();
        void test2();
        void findElementsMatchingHashes(
            int, const std::set<int>&, const std::vector<HashFunction*>&, 
            std::vector<int>&, std::vector<int>&
        );
};

#endif
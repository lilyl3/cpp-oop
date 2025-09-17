#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <vector>

class BitArray {
    private:
        int size;
        bool* bits;         // dynamically allocate
    public:
        BitArray(int m);
        ~BitArray();        // destructor to free memory
        void setBits(const std::vector<int>& positions);
        bool areAllBitsSet(const std::vector<int>& positions) const;
};

#endif
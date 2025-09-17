#include "bit_array.h"
#include <vector>
#include <stdexcept>

using namespace std;

BitArray::BitArray(int m){
    size = m;
    bits = new bool[m];
    // initialize all bits to 0
    for (int i = 0; i < m; i++){
        bits[i] = false;
    }
}

BitArray::~BitArray(){
    // deallocate
    delete[] bits;
}

// Set bits to true at given positions
void BitArray::setBits(const vector<int>& positions){
    for (int pos : positions) {
        if (pos < 0 || pos >= size) throw invalid_argument("@BitArray: pos is out-of-range.");
        bits[pos] = true;
    }
}

// Check if all bits are set to true at given positions
bool BitArray::areAllBitsSet(const vector<int>& positions) const{
    for (int pos : positions) {
        if (pos < 0 || pos >= size) throw invalid_argument("@BitArray: pos is out-of-range.");
        if (!bits[pos]) return false;
    }
    return true;
}
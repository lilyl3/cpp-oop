#include "resource_manager.h"

// Deconstructor
ResourceManager::~ResourceManager() {
    delete[] data;
}

// Constructor
ResourceManager::ResourceManager(unsigned int size) : size(size), data(new int[size]) {} 

// Copy (Deep) constructor
ResourceManager::ResourceManager(
    const ResourceManager& ref
) : size(ref.size), data(new int[size]) {
    for (int i = 0; i < size; i++){
        data[i] = ref.data[i];
    }
}

// Move constructor
ResourceManager::ResourceManager noexcept(
    ResourceManager&& ref
) : size(ref.size) 
{
    data = ref.data;
    ref.data = nullptr;
    ref.size = 0;
}

// Copy Assignment
ResourceManager& operator=(const ResourceManager& ref) {
    if (this != &ref) {
        delete[] data;
        size = ref.size;
        data = new int[size];

        for (int i = 0; i < size; i++){
            data[i] = ref.data[i];
        }
    }

    return *this;
}

// Move Assignment
ResourceManager& operator=(ResourceManager&& ref) noexcept{
    if (this != &ref) {
        delete[] data;
        // All member functions of a class can access private members of ANY instance of same class
        size = ref.size;
        data = ref.data;

        ref.data = nullptr;
        ref.size = 0;
    }

    return *this;
}

// Accessors
int* ResourceManager::getData() {
    return data;
}

const int* ResourceManager::getData() const {
    return data;
}

unsigned int ResourceManager::getSize() const {
    return size;
}
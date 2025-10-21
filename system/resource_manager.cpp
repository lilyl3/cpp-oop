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
) : size(ref.getSize()), data(new int[size]) {
    for (int i = 0; i < size; i++){
        data[i] = ref.getData()[i];
    }
}

// Move constructor
ResourceManager::ResourceManager noexcept(
    ResourceManager&& ref
) : size(ref.getSize()) 
{
    data = ref.getData();
    ref.resetData(nullptr);
    ref.setSize(0);
}

// Copy Assignment
ResourceManager& operator=(const ResourceManager& ref) {
    if (this != &ref) {
        delete[] data;
        size = ref.getSize();
        data = new int[size];

        int* refResource = ref.getData();
        for (int i = 0; i < size; i++){
            data[i] = refResource[i];
        }
    }

    return *this;
}

// Move Assignment
ResourceManager& operator=(ResourceManager&& ref) noexcept{
    if (this != &ref) {
        delete[] data;
        size = ref.getSize();
        data = ref.getData();

        ref.resetData(nullptr);
        ref.setSize(0);
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

void ResourceManager::resetData(int* newData) {
    if (data != newData){
        delete[] data;
        data = newData;
    }
}

void ResourceManager::setSize(unsigned int newSize) {
    size = newSize;
}
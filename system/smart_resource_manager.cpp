#include "smart_resource_manager.h"
using namespace std;

SmartResourceManager::~SmartResourceManager(){
    data.reset();   // Deletes owned object and resets to null
}

// Constructor
SmartResourceManager::SmartResourceManager(
    unsigned int size
) : size(size), data(new int[size]){}

// Move constructor
// No issue of self-assignment because object not created yet
SmartResourceManager::SmartResourceManager(
    SmartResourceManager&& ref
) : size(ref.size), data(std::move(ref.data))
{
    ref.size = 0;
}

// Move assignment
SmartResourceManager& SmartResourceManager::operator=(SmartResourceManager&& ref){
    // Check for self-assignment
    if (this != &ref) {
        data = std::move(ref.data);
        ref.size = 0;
    }
    return *this;
}
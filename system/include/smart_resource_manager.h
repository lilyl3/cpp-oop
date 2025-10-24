#ifndef SMART_RESOURCE_MANAGER_H
#define SMART_RESOURCE_MANAGER_H

class SmartResourceManager {
private:
    std::unique_ptr<int[]> data;
    unsigned int size;
public:
    ~SmartResourceManager();

    // Constructor
    SmartResourceManager(unsigned int);
    SmartResourceManager(SmartResourceManager&&); // Move

    // Move assignment
    SmartResourceManager& operator=(SmartResourceManager&&);
};

#endif
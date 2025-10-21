#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

class ResourceManager {
private:
    int* data;
    unsigned int size;
public:
    // Destructor
    ~ResourceManager();

    // Constructors
    ResourceManager(unsigned int);
    ResourceManager(const ResourceManager&);                // Copy
    ResourceManager(ResourceManager&&) noexcept;            // Move

    // Copy Assignment
    ResourceManager& operator=(const ResourceManager&);
    // Move Assignment
    ResourceManager& operator=(ResourceManager&&) noexcept;

    // Accessors
    int* getData();
    const int* getData() const;
    unsigned int getSize() const;
};

#endif
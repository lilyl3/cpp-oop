#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

#include <functional>

class HashFunction {
    protected:
        int m;  // size of BitArray
    public:
        HashFunction(int m) : m(m) {}
        virtual ~HashFunction() = default;
        virtual int hash(int element) = 0;
};

class ModularHash : public HashFunction {
    public:
        ModularHash(int m) : HashFunction(m) {}
        int hash(int element) override {
            return element % m;
        }
};

class MultiplicativeHash : public HashFunction {
    private:
        int a, b;
    public:
        MultiplicativeHash(int m, int a, int b) : HashFunction(m), a(a), b(b) {}
        int hash(int element) override {
            return (a * element + b) % m;
        }
};

class StdHash : public HashFunction {
    public:
        StdHash(int m) : HashFunction(m) {}
        int hash(int element) override {
            return std::hash<int>{} (element) % m;
        }
};

#endif
#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

class HashFunction {
    public:
        virtual ~HashFunction() = default;
        virtual int hash(int element) = 0;
};

#endif
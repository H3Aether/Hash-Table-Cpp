#pragma once
#include <string>
using namespace std;

/*---------------------------------HashTable---------------------------------*/
/*-------------------------   HASH FUNCTION CLASS   -------------------------*/
/*---------------------------------------------------------------------------*/

enum HashFunctionType {POLYNOMIAL_ROLLING, DJB2};

class HashFunction{
    public:
        HashFunction(unsigned long int n, HashFunctionType hash_type) : table_size(n), type(hash_type) {};
        unsigned long int hash(const string& key) const;

        unsigned long int polynomialRolling(const string& key) const;
        unsigned long int djb2(const string& key) const;

    private:
        unsigned long int table_size;
        HashFunctionType type;
};
#include "hash_function.hpp"

unsigned long int HashFunction::hash(const string& key) const{
    switch (type){
        case POLYNOMIAL_ROLLING:
            return polynomialRolling(key); break;
        case DJB2:
            return djb2(key); break;
        default:
            return 0; break;
    }
}



unsigned long int HashFunction::polynomialRolling(const string& key) const{
    unsigned long int hash = 0;
    unsigned long int p_pow = 1;
    for (int i = 0; key[i] != '\0'; i++){
        hash += (tolower(key[i]) - 'a' + 1) * p_pow;
        p_pow *= 31;
    }
    return hash % table_size;
}

unsigned long int HashFunction::djb2(const string& key) const{
    unsigned long int hash = 5381;
    int c;
    for (int i = 0; key[i] != '\0'; i++){
        c = tolower(key[i]);
        hash = ((hash << 5) + hash) + c;
    }
    return hash % table_size;
}
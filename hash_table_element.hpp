#pragma once
using namespace std;

template <class K, class V>
class HashTableElement{
    public:
        HashTableElement(const K& k, const V& v) : key(k), value(v) {};
        HashTableElement(const K& k) : key(k), value() {};
        HashTableElement() : key(), value() {};
        ~HashTableElement() {};

        K getKey() const {return key;};
        V getValue() const {return value;};

    private:
        K key;
        V value;
};
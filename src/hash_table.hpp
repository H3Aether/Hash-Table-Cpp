#pragma once
#include "hash_table_element.hpp"
#include "hash_function.hpp"
#include <list>
#include <iostream>
using namespace std;

/*---------------------------------HashTable---------------------------------*/
/*--------------------------   HASH TABLE CLASS   ---------------------------*/
/*---------------------------------------------------------------------------*/

template <class T>
class HashTable{
    public:
        HashTable(unsigned long int n, HashFunctionType hash_type);
        ~HashTable() {delete[] table;};

        void insert(const T& element);
        void find(T* element) const;
        void remove(const T& element);
        void display() const;

    private:
        list<T>* table;
        size_t size;
        HashFunction hash_function;
};

template<class T>
HashTable<T>::HashTable(unsigned long int n, HashFunctionType hash_type) : hash_function(n, hash_type){
    size = n;
    table = new list<T>[size];
}

template <class T>
void HashTable<T>::insert(const T& element){
    int index = hash_function.hash(element.getKey());
    table[index].push_back(element);
}

template <class T>
void HashTable<T>::find(T* element) const{
    int index = hash_function.hash(element->getKey());
    for(auto it = table[index].begin(); it != table[index].end(); it++){
        if(it->getKey() == element->getKey()){
            *element = *it;
            return;
        }
    }
    *element = T();
}

template <class T>
void HashTable<T>::remove(const T& element){
    int index = hash_function.hash(element.getKey());
    for (auto it = table[index].begin(); it != table[index].end(); it++){
        if (it->getKey() == element.getKey()){
            table[index].erase(it);
            return;
        }
    }
}




template <class T>
void HashTable<T>::display() const{
    for(int i=0; i<size; i++){
        cout << "Index " << i << ": | ";
        for(auto it = table[i].begin(); it != table[i].end(); it++){
            cout << it->getKey() << " " << it->getValue() << " | ";
        }
        cout << endl;
    }
}
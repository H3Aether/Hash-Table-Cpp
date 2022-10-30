#pragma once
#include "hash_table_element.hpp"
#include "hash_function.hpp"
#include <list>
#include <iostream>
#include <iomanip>
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
        void printStatistics() const;


    private:
        list<T>* table;
        size_t size;
        HashFunction hash_function;
        unsigned long int entries;
        unsigned long int empty_cells;
        unsigned long int collisions;
};

template<class T>
HashTable<T>::HashTable(unsigned long int n, HashFunctionType hash_type) : hash_function(n, hash_type){
    size = n;
    table = new list<T>[size];
    entries = 0;
    empty_cells = size;
    collisions = 0;
}

template <class T>
void HashTable<T>::insert(const T& element){
    int index = hash_function.hash(element.getKey()); 

    // Updating data
    entries++;
    if (table[index].empty()){
        empty_cells--;
    } else {
        collisions++;
    }

    table[index].push_back(element); // Inserting element
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
void HashTable<T>::printStatistics() const{
    cout << "HASH TABLE STATISTICS:" << endl;
    cout << "|   Table size......................" << size << endl;
    cout << "|   Number of entries..............." << entries << " (" << fixed << setprecision(0) << (float)entries/size*100 << "% of table size)" << endl;
    cout << "|   Number of empty cells..........." << empty_cells << " (" << (float)empty_cells/size*100 << "% of table size)" << endl;
    cout << "|   Number of collisions............" << collisions << endl;
    cout << "|   Avg nb of elements per cell....." << setprecision(2) << (float)entries/(size-empty_cells) << endl;
}
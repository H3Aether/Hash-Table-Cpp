#pragma once
#include <string>
#include <iostream>
using namespace std;

template <class T>
class Error{ // Abstract class
    public:
        Error(const T& e) : element(e) {};
        virtual void virtualMethod() const = 0;
    protected:
        T element;
};

template <class T>
class ElementAlreadyExists : public Error<T>{
    public:
        ElementAlreadyExists(const T& e) : Error<T>(e) {};
        void virtualMethod() const{};
        friend ostream& operator<<(ostream& os, const ElementAlreadyExists& eae){
            os << "ERROR: Element with key " << eae.element.getKey() << " already exists in the hash table." << endl;
            return os;
        }
};

template <class T>
class ElementDoesNotExist : public Error<T>{
    public:
        ElementDoesNotExist(const T& e) : Error<T>(e) {};
        void virtualMethod() const{};
        friend ostream& operator<<(ostream& os, const ElementDoesNotExist& ede){
            os << "ERROR: Element with key " << ede.element.getKey() << " does not exist in the hash table." << endl;
            return os;
        }
};
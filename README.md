# **Implementing hash tables in C++**

Hash tables are a data structure that allows for fast lookup of data. I want to demonstrate their use with this project. This code is a simple, yet versatible implementation, due to the use of templates.

## An example using NASA/JPL's Small-Body Database

The SBDB regroups over 1,250,000 objects in the Solar System. The data was retrieved using the [Query API](https://ssd-api.jpl.nasa.gov/doc/sbdb_query.html), and processed to a CSV file using Python (see [this script](./src/NASA_JPL_SBDB/fetch_data.py)).
The elements are inserted into a hash table, using their SPK-ID as the key. The SPK-ID is a unique identifier for each object in the SBDB. The hash table is then used to retrieve the data for a given object.

## How to use

Before creating the hash table, it is necessary to create a type or a class for the data, based on the HashTableElement template. For simple data, a typedef is sufficient:
    
```c++
typedef HashTableElement<string, int> MyData;
```

For more complex data, creating a subclass is necessary:
    
```c++
typedef struct{
    int value1;
    string value2;
    float value3;
} ValueType;

class MyData : public HashTableElement<string, ValueType> {
    MyData(); // Default constructor
    MyData(const string& key, const ValueType& value); // Complete constructor
    MyData(const string& key); // I recommend creating this constructor to use later in the find() and remove() methods

    // Overloading the << operator to print the data can be convenient
};
```

Then the hash table can be created and used:
    
```c++
HashTable<string, MyData> myHashTable(101, DJB2); // The size of the hash table is 101, and the hash function is DJB2

MyData data1("key1", {12, "hello", 1.0});
myHashTable.insert(data1);

MyData data_search("key1");
myHashTable.find(&data_search); // The value of data_search is now updated with the data found in the hash table

MyData data_search("key1");
myHashTable.remove(data_search); // The corresponding element is removed from the hash table

myHashTable.printStatistics(); // Displays all there is to know about the hash table
myHashTable.print(); // Displays all the elements in the hash table. Make sure you overloaded the << operator for your data type, and be careful as this can be a lot of data
```

## Hash functions

The hash function is a function that takes a key and returns an index in the hash table. It plays a crucial role in the performance of the hash table. 4 are implemented in this project:
- POLYNOMIAL ROLLING: A widely used hash function to deal with *string* keys.
- DJB2: A more advanced hash function for *string* keys (cf [this website](http://www.cse.yorku.ca/~oz/hash.html))
- DIVISION: The simplest hash function, using the modulo operator on *ints*.
- INTEGER 32: A hash function I found on [this website](https://burtleburtle.net/bob/hash/integer.html), created by a certain Thomas Wang. I gave it this name because it works for 32-bit *ints*.

Adding a new hash function is easy, as long as it takes a key and returns an index in the hash table. First, add it to the [hash_function.hpp](./src/hash_function.hpp) enum:
        
```c++
enum HashFunctionType {POLYNOMIAL_ROLLING, DJB2, DIVISION, INTEGER_32, MY_HASH_FUNCTION};
```

Then, add the function to the [hash_function.hpp](./src/hash_function.hpp) HashFunction class:
    
```c++
class HashFunction{
    public:
        ...
        unsigned long int myHashFunction(const int& key) const;
        ...
};
```

Finally, add the function to the switch in the [hash_function.cpp](./src/hash_function.cpp) HashFunction::hash() method. If the hash function takes a key of a different type than *int* or *string*, overload the method.
        
```c++
unsigned long int HashFunction::hash(const string& key) const {
    switch(type){
        ...
        case MY_HASH_FUNCTION:
            return myHashFunction(key);
        ...
    }
}
```

## Error handling

Some functions can fail for different reasons. In that case, they throw an exception. The exceptions are defined in the [error.hpp](./src/error.hpp) file.

- HashTable::insert() : If an element with the same key already exists in the hash table, an exception of type *ElementDoesNotExist* is thrown.

- HashTable::find() : If the element is not found, an exception of type *ElementNotFound* is thrown.

- HashTable::remove() : If the element does not exist in the database, an exception of type *ElementDoesNotExist* is thrown.

## Compilation

The project can be compiled using the [Makefile](./src/akefile) with the command `make`.

## Conclusion

This project is a simple way of demonstrating the power of hash tables. Searching a specific entry in a table filled with more than a million elements is instant.
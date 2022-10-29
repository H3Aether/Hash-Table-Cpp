#include "hash_table.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

typedef HashTableElement<string, int> Person;
typedef HashTableElement<string, string> User;

void fileHashTable(){
    // Reading users and passwords from files
    HashTable<User> users(1300021, DJB2);

    ifstream u_file("users.txt");
    ifstream p_file("passwords.txt");
    for(int i=0; i<990000; i++){
        string user, password;
        u_file >> user;
        p_file >> password;
        User u(user, password);
        users.insert(u);
    }
    u_file.close();
    p_file.close();
    
    User u_sparing = users.find(User("sparing"));
    cout << "User: " << u_sparing.getKey() << " Password: " << u_sparing.getValue() << endl;
}


int main(){
    cout << "Hash Table" << endl;
    // HashTable<Person> h1(10, POLYNOMIAL_ROLLING);
    // string names[10] = {"John", "Paul", "George", "Ringo", "Pete", "Alexis", "Dennis", "Stuart", "Roger", "Mick"};
    // int ages[10] = {78, 12, 34, 6, 45, 23, 56, 47, 89, 90};
    // for(int i=0; i<10; i++){
    //     Person e(names[i], ages[i]);
    //     h1.insert(e);
    // }
    // h1.display();

    clock_t tStart = clock();
    fileHashTable();
    cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << endl;

    return 1;
}
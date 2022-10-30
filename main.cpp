#include "hash_table.hpp"
#include <iostream>
#include <fstream>
using namespace std;

typedef HashTableElement<string, string> User;

HashTable<User> createUsersHashTable(){
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
    return users;
}

ostream& operator<<(ostream& os, const User& u){
    os << "USER: " << u.getKey() << ":" << u.getValue();
    return os;
}


int main(){
    HashTable<User> users = createUsersHashTable();

    bool running = true;
    while(running){
        cout << "Enter username: ";
        string username;
        cin >> username;
        if(username == "exit"){
            running = false;
            continue;
        }
        User user_search = User(username);
        users.find(&user_search);
        if (user_search.getKey() == ""){
            cout << "User not found" << endl;
        } else {
            cout << user_search << endl;
        }
    }

    return 1;
}
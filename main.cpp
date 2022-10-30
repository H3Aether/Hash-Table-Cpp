#include "./src/hash_table.hpp"
#include "./src/NASA_JPL_SBDB/NASA_JPL_SBDB.hpp"
#include <typeinfo>
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
    
    cout << "Loading SBDB..." << endl;
    vector<SmallBody> small_bodies = readSmallBodiesDataBase();

    cout << "SBDB loaded." << endl << "Creating hash table..." << endl;
    HashTable<SmallBody> sbdb_table(1627601, LAZY_INTEGER);
    for(SmallBody sb : small_bodies){
        sbdb_table.insert(sb);
    }
    cout << "Hash table created." << endl;

    bool running = true;
    while(running){
        cout << "Enter SPK-ID: ";
        string spkid;
        cin >> spkid;
        if(spkid == "exit"){
            running = false;
            continue;
        }
        SmallBody sb_search = SmallBody(stoi(spkid));
        sbdb_table.find(&sb_search);
        if (sb_search.getKey() == 0){
            cout << "Body not found" << endl;
        } else {
            cout << endl << sb_search << endl;
        }
    }

    return 1;
}
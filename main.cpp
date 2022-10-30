#include "./src/hash_table.hpp"
#include "./src/NASA_JPL_SBDB/NASA_JPL_SBDB.hpp"
using namespace std;

int main(){
    cout << "Loading SBDB..." << endl;
    vector<SmallBody> small_bodies = readSmallBodiesDataBase();

    cout << "SBDB loaded." << endl << "Creating hash table..." << endl;
    HashTable<SmallBody> sbdb_table(1627601, INTEGER_32);
    for(SmallBody sb : small_bodies){
        sbdb_table.insert(sb);
    }
    small_bodies.clear(); // Free memory
    cout << "Hash table created." << endl;

    sbdb_table.printStatistics();
    cout << endl;

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
        try{
            sbdb_table.find(&sb_search);
            cout << endl << sb_search << endl;
        }
        catch(ElementDoesNotExist<SmallBody> enf){
            cout << endl << enf << endl;
        }
    }

    return 1;
}
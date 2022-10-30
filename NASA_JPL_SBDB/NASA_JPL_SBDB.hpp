#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

enum Kind {AN, AU, CN, CU}; // Asteroid, Asteroid-Unnumbered, Comet, Comet-Unnumbered
Kind stringToKind(const string& str_kind);
string kindToString(const Kind& kind);

class SmallBody{
    public:
        SmallBody();
        SmallBody(const string& spkid, const string& full_name, const string& kind, const string& pdes, const string& name, const string& moid, const string& diameter, const string& GM, const string& density, const string& albedo);
        ~SmallBody() {};

        friend ostream& operator<<(ostream& os, const SmallBody& sb);

    private:
        int spkid; // primary SPK-ID
        string full_name; // full designation (and name)
        Kind kind; //  	indicates whether asteroid (a) or comet (c) and whether numbered (n) or unnumbered (u); for example a value of an indicates a numbered asteroid and cu indicates an unnumbered comet
        int pdes; // primary designation (for numbered asteroids, this is the IAU number)
        string name; // IAU name (if any)
        float moid; // minimum distance between the orbits of Earth and the small-body (au)
        float diameter; // effective body diameter (km)
        float GM; // mass expressed as a product of the mass “M” and gravitational constant “G” (km3/s2)
        float density; // bulk density (g/cm3)
        float albedo; // geometric albedo
};

vector<SmallBody> readSmallBodiesDataBase(const string& filename);
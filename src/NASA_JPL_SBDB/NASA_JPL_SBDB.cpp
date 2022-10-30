#include "NASA_JPL_SBDB.hpp"
using namespace std;

Kind stringToKind(const string& str_kind){
    if(str_kind == "an"){
        return AN;
    } else if(str_kind == "au"){
        return AU;
    } else if(str_kind == "cn"){
        return CN;
    } else{
        return CU;
    }
}

string kindToString(const Kind& kind){
    switch(kind){
        case AN:
            return "Asteroid Numbered";
        case AU:
            return "Asteroid Unnumbered";
        case CN:
            return "Comet Numbered";
        default:
            return "Comet Unnumbered";
    }
}

SmallBody::SmallBody(){
    key = 0;
    value.full_name = "";
    value.kind = AN;
    value.pdes = 0;
    value.name = "0";
    value.moid = 0.0;
    value.diameter = 0.0;
    value.GM = 0.0;
    value.density = 0.0;
    value.albedo = 0.0;
}

SmallBody::SmallBody(const string& spkid, const string& full_name, const string& kind, const string& pdes, const string& name, const string& moid, const string& diameter, const string& GM, const string& density, const string& albedo){
    this->key = stoi(spkid);
    this->value.full_name = full_name;
    this->value.kind = stringToKind(kind);
    this->value.pdes = stoi(pdes);
    this->value.name = name;
    this->value.moid = stof(moid);
    this->value.diameter = stof(diameter);
    this->value.GM = stof(GM);
    this->value.density = stof(density);
    this->value.albedo = stof(albedo);
}

ostream& operator<<(ostream& os, const SmallBody& sb){
    os << "SPK-ID: " << sb.key << endl;
    os << "Full Name: " << sb.value.full_name << endl;
    os << "Kind: " << kindToString(sb.value.kind) << endl;
    os << "Primary Designation: " << sb.value.pdes << endl;
    os << "Name: ";
    if(sb.value.name == "0"){ os << "N/A" << endl;} else{ os << sb.value.name << endl;}
    os << "Minimum Orbit Intersection Distance: ";
    if(sb.value.moid == 0){ os << "N/A" << endl;} else{ os << sb.value.moid << " au" << endl;}
    os << "Diameter: ";
    if(sb.value.diameter == 0){ os << "N/A" << endl;} else{ os << sb.value.diameter << " km" << endl;}
    os << "GM: ";
    if(sb.value.GM == 0){ os << "N/A" << endl;} else{ os << sb.value.GM << " km3/s2" << endl;}
    os << "Density: ";
    if(sb.value.density == 0){ os << "N/A" << endl;} else{ os << sb.value.density << " g/cm3" << endl;}
    os << "Albedo: ";
    if(sb.value.albedo == 0){ os << "N/A" << endl;} else{ os << sb.value.albedo << endl;}
    return os;
}

vector<SmallBody> readSmallBodiesDataBase(){
    vector<SmallBody> SB_DATABASE;
    ifstream file("./src/NASA_JPL_SBDB/data.csv");
    if (!file.is_open()){
        cout << "Error opening database file" << endl;
        return SB_DATABASE;
    }
    string line;
    string spkid, full_name, kind, pdes, name, moid, diameter, GM, density, albedo;

    while(getline(file, line)){
        stringstream ss(line);
        getline(ss, spkid, ',');
        getline(ss, full_name, ',');
        getline(ss, kind, ',');
        getline(ss, pdes, ',');
        getline(ss, name, ',');
        getline(ss, moid, ',');
        getline(ss, diameter, ',');
        getline(ss, GM, ',');
        getline(ss, density, ',');
        getline(ss, albedo, ',');

        SmallBody sb(spkid, full_name, kind, pdes, name, moid, diameter, GM, density, albedo);
        SB_DATABASE.push_back(sb);
    }
    file.close();
    return SB_DATABASE;
}
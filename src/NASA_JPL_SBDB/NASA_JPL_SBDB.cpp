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
    spkid = 0;
    full_name = "";
    kind = AN;
    pdes = 0;
    name = "";
    moid = 0.0;
    diameter = 0.0;
    GM = 0.0;
    density = 0.0;
    albedo = 0.0;
}

SmallBody::SmallBody(const string& spkid, const string& full_name, const string& kind, const string& pdes, const string& name, const string& moid, const string& diameter, const string& GM, const string& density, const string& albedo){
    this->spkid = stoi(spkid);
    this->full_name = full_name;
    this->kind = stringToKind(kind);
    this->pdes = stoi(pdes);
    this->name = name;
    this->moid = stof(moid);
    this->diameter = stof(diameter);
    this->GM = stof(GM);
    this->density = stof(density);
    this->albedo = stof(albedo);
}

ostream& operator<<(ostream& os, const SmallBody& sb){
    os << "SPK-ID: " << sb.spkid << endl;
    os << "Full Name: " << sb.full_name << endl;
    os << "Kind: " << kindToString(sb.kind) << endl;
    os << "Primary Designation: " << sb.pdes << endl;
    os << "Name: " << sb.name << endl;
    os << "Minimum Orbit Intersection Distance: ";
    if(sb.moid == 0){ os << "N/A" << endl;} else{ os << sb.moid << " au" << endl;}
    os << "Diameter: ";
    if(sb.diameter == 0){ os << "N/A" << endl;} else{ os << sb.diameter << " km" << endl;}
    os << "GM: ";
    if(sb.GM == 0){ os << "N/A" << endl;} else{ os << sb.GM << " km3/s2" << endl;}
    os << "Density: ";
    if(sb.density == 0){ os << "N/A" << endl;} else{ os << sb.density << " g/cm3" << endl;}
    os << "Albedo: ";
    if(sb.albedo == 0){ os << "N/A" << endl;} else{ os << sb.albedo << endl;}
    return os;
}

vector<SmallBody> readSmallBodiesDataBase(){
    vector<SmallBody> SB_DATABASE;
    ifstream file("./NASA_JPL_SBDB/data.csv");
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
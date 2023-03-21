//
// Created by marco on 15/03/2023.
//

#include "Station.h"
using namespace std;

Station::Station(const string& name, const string& district,const string& municipality,
                 const string& township, const string& line)
                 :name(name),district(district),municipality(municipality),township(township),line(line)
                 {}

Station::Station() = default;

string Station::getName() const {return name;}
string Station::getDistrict() const {return district;}
string Station::getMunicipality() const {return municipality;}
string Station::getTownship() const {return township;}
string Station::getLine() const {return line;}

void Station::setName(const string &name) {this->name = name;}
void Station::setDistrict(const string &district) {this->district = district;}
void Station::setMunicipality(const string &municipality) {this->municipality = municipality;}
void Station::setTownship(const string &township) {this->township = township;}
void Station::setLine(const string &line) {this->line = line;}

bool Station::operator==(Station &a) const {
    return a.getName() == name && a.getDistrict() == district &&
    a.getLine() == line && a.getMunicipality() == municipality &&
    a.getTownship() == township;
}



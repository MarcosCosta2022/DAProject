//
// Created by marco on 15/03/2023.
//

#include "Network.h"
#include <string>

using namespace std;

Network::Network(std::string StationA, std::string StationB, std::string capacity, std::string service){
    stationA = StationA;
    stationB = StationB;
    Capacity = capacity;
    Service = service;
}

string Network::getStationA() {
    return stationA;
}

string Network::getStationB() {
    return stationB;
}

string Network::getCapacity() {
    return Capacity;
}

string Network::getService() {
    return Service;
}

string Network::setStationA(string sA) {
    stationA = sA;
}

string Network::setStationB(string sB) {
    stationB = sB;
}

string Network::setCapacity(string C) {
    Capacity = C;
}

string Network::setService(string S) {
    Service = S;
}

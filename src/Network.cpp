//
// Created by marco on 15/03/2023.
//

#include "Network.h"

Network::Network(std::string StationA, std::string StationB, std::string capacity, std::string service){
    stationA = StationA;
    stationB = StationB;
    this->capacity = capacity;
    this->service = service;
}

const string &Network::getStationA() const {return stationA;}
void Network::setStationA(const string &stationA) {this->stationA = stationA;}
const string &Network::getStationB() const {return stationB;}
void Network::setStationB(const string &stationB) {this->stationB = stationB;}
const string &Network::getCapacity() const {return capacity;}
void Network::setCapacity(const string &capacity){this->capacity = capacity;}
const string &Network::getService() const {return service;}
void Network::setService(const string &service) {this->service = service;}



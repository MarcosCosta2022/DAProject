//
// Created by marco on 15/03/2023.
//

#ifndef PROJECT_NETWORK_H
#define PROJECT_NETWORK_H

#include <string>

using namespace std;

class Network {

public:
    Network(std::string stationA, std::string stationB, int capacity, std::string service);
private:
    std::string stationA;
public:
    const string &getStationA() const;

    void setStationA(const string &stationA);

    const string &getStationB() const;

    void setStationB(const string &stationB);

    int getCapacity() const;

    void setCapacity(int capacity);

    const string &getService() const;

    void setService(const string &service);

    bool operator==(const Network& a) const;
private:
    std::string stationB;
    int capacity;
    std::string service;
};


#endif //PROJECT_NETWORK_H

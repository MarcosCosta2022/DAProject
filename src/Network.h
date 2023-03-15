//
// Created by marco on 15/03/2023.
//

#ifndef PROJECT_NETWORK_H
#define PROJECT_NETWORK_H
#include <string>

class Network {

public:
    Network(std::string StationA, std::string StationB, std::string capacity, std::string service);

    std::string getStationA();
    std::string getStationB();
    std::string getCapacity();
    std::string getService();

    std::string setStationA(std::string sA);
    std::string setStationB(std::string sB);
    std::string setCapacity(std::string C);
    std::string setService(std::string S);
private:
    std::string stationA;
    std::string stationB;
    std::string Capacity;
    std::string Service;
};


#endif //PROJECT_NETWORK_H

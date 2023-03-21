//
// Created by marco on 15/03/2023.
//

#ifndef PROJECT_TRAINMANAGER_H
#define PROJECT_TRAINMANAGER_H

#include <unordered_map>
#include "../data_structures/Graph.h"

class MyHashFunction {
public:
    size_t operator()(const Network& p) const
    {
        return p.getStationA().length() + p.getStationB().length() + p.getService().length() + p.getCapacity().length();
    }
};

class TrainManager {
public:
    TrainManager();
    void LoadStations();
    void LoadNetworks();
private:
    Graph trainNetwork;
    unordered_map<std::string,Station> stations;
    unordered_map<Network,double,MyHashFunction> networks;

};



#endif //PROJECT_TRAINMANAGER_H

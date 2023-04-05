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
        return p.getStationA().length() + p.getStationB().length() + p.getService().length() + p.getCapacity();
    }
};

class TrainManager {
public:
    TrainManager();
    void LoadStations();
    void LoadNetworks();
    void maxFlowOfTrains();
    void calculateMaxFlowFromNetworkToSingleStation();
    void stations_most_amount_trains();
    void calculateMaxFlowWithMinimumCost();
    void useSubGraph();


    string getAnswer();
    Vertex* getStationFromUser();
    pair<Vertex*,Vertex*> getStationsFromUser();
private:
    Graph trainNetwork;
    unordered_map<std::string,Station> stations; // if these will only be used one time, its better to create them in the function they are used
    unordered_map<Network,double,MyHashFunction> networks;



};



#endif //PROJECT_TRAINMANAGER_H

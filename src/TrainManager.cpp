//
// Created by marco on 15/03/2023.
//
#include "TrainManager.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Network.h"
using namespace std;

TrainManager::TrainManager() {
    LoadStations();
    LoadNetworks();
}

void TrainManager::LoadStations() {
    string n, d, m, t, l, line;
    int count = 0;
    ifstream in; in.open("../resources/stations.csv");
    if(!in) cerr << "Could not open the file!" << endl;
    getline(in,line);
    while(getline(in,line)) {
        istringstream iss(line);
        count++;
        getline(iss, n, ','); getline(iss, d, ','); getline(iss, m, ',');
        getline(iss,t, ','); getline(iss,l);
        Station a = Station(n,d,m,t,l);
        auto it = stations.find(n);
        if(it==stations.end()){
            stations.emplace(n,a); //definir hash?
            trainNetwork.addVertex(a);
        }
    }
}
void TrainManager::LoadNetworks() {
    string sA, sB, cap, serv, line;
    double w = 0;
    ifstream in; in.open("../resources/network.csv");
    if(!in) cerr << "Could not open the file! " << endl;
    getline(in, line);
    while(getline(in,line)) {
        istringstream iss(line);
        getline(iss, sA, ','); getline(iss, sB, ',');
        getline(iss, cap, ','); getline(iss, serv, ',');
        Network a = Network(sA,sB,cap,serv);
        auto it = networks.find(a);
        if(it==networks.end()) {
            networks.emplace(a,w);
            auto it2 = stations.find(sA);
            auto it3 = stations.find(sB);
            trainNetwork.addEdge(it2->second,it3->second,a);
        }
    }
}

Vertex *TrainManager::getStationFromUser() {
    string name;
    cin >> name;
    if (cin.fail()){
        cin.clear();
        return nullptr;
    }
    Vertex* station = trainNetwork.findVertexByName(name);
    return station;
}


void TrainManager::maxFlowOfTrains() {
    auto stations_input = getStationsFromUser();
    Vertex* s = stations_input.first;
    Vertex* t = stations_input.second;
    if (s == nullptr || t == nullptr || s == t){
        printf("Invalid stations!\n");
    }

}

pair<Vertex*,Vertex*> TrainManager::getStationsFromUser() {
    printf("What is the name of the source station?");
    Vertex* source = getStationFromUser();
    printf("What is the name of the target station?");
    Vertex* target = getStationFromUser();
    return {source,target};
}

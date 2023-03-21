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
    ifstream in; in.open(R"(/home/joao44/projetoAED 2.0/data/airports.csv)"); // depois cada um coloca o seu path quando quiser testar
    if(!in) cerr << "Could not open the file!" << endl;
    getline(in,line);
    while(getline(in,line)) {
        istringstream iss(line);
        count++;
        getline(iss, n, ','); getline(iss, d, ','); getline(iss, m, ',');
        getline(iss,t, ','); getline(iss,l,',');
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
    ifstream in; in.open(R"(/home/joao44/projetoAED 2.0/data/airports.csv)"); //depois cada um coloca o seu path quando quiser testar
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
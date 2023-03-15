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
void TrainManager::LoadNetworks() {
    string sA, sB, cap, serv, line;
    ifstream in; in.open(); //depois cada um coloca o seu path quando quiser testar
    if(!in) cerr << "Could not open the file! " << endl;
    getline(in, line);
    while(getline(in,line)) {
        istringstream iss(line);
        getline(iss, sA, ','); getline(iss, sB, ',');
        getline(iss, cap, ','); getline(iss, serv, ',');
        Network a = Network(sA,sB,cap,serv);
        if(trainNetwork.findVertex())
    }
}
void TrainManager::LoadStations() {
    string name;
}
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
            stations.emplace(n,a);
            trainNetwork.addVertex(a);
        }
    }
}
void TrainManager::LoadNetworks() {
    int cap;
    string sA, sB, serv, line;
    double w = 0;
    ifstream in; in.open("../resources/network.csv");
    if(!in) cerr << "Could not open the file! " << endl;
    getline(in, line);
    while(getline(in,line)) {
        istringstream iss(line);
        getline(iss, sA, ','); getline(iss, sB, ',');
        iss >> cap; iss.ignore(1); getline(iss, serv, ',');
        Network a = Network(sA,sB,cap,serv);
        pair<int,string> weight = make_pair(cap,serv);
        auto it = networks.find(a);
        if(it==networks.end()) {
            networks.emplace(a,w);
            auto it2 = stations.find(sA);
            auto it3 = stations.find(sB);
            trainNetwork.addBidirectionalEdge(it2->second,it3->second,cap , serv);
        }
    }
}


void TrainManager::stations_most_amount_trains() {
    unsigned long max = 0;
    vector<pair<Vertex*,Vertex*>> res;
    for (int i = 0 ; i < trainNetwork.getNumVertex();i++){
        for (int j = i+1 ; j < trainNetwork.getNumVertex();j++){
            unsigned long temp = trainNetwork.edmondsKarp(trainNetwork.getVertexSet()[i],trainNetwork.getVertexSet()[j]);
            if (temp > max){
                res.clear();
                max = temp;
                res.emplace_back(trainNetwork.getVertexSet()[i],trainNetwork.getVertexSet()[j]);
            }
            else if (temp == max){
                res.emplace_back(trainNetwork.getVertexSet()[i],trainNetwork.getVertexSet()[j]);
            }
        }
    }
    for (auto& p : res){
        cout << p.first->getStation().getName() << " and " << p.second->getStation().getName() << '\n';
    }
    /*
    int max = 0;
    vector<pair<Station,Station>> final;
    for(auto v: trainNetwork.getVertexSet()) v->setVisited(false);
    for (auto v : trainNetwork.getVertexSet()) {
        v->setVisited(true);
        for (auto e : v->getAdj()) {
            if (e->getWeight() > max && !(e->getDest()->isVisited())) {
                final.clear();
                max = e->getWeight();
                final.push_back(make_pair(e->getOrig()->getStation(), e->getDest()->getStation()));
                continue;
            }
            if (e->getWeight() == max && !(e->getDest()->isVisited())) {
                final.push_back(make_pair(e->getOrig()->getStation(), e->getDest()->getStation()));
                continue;
            }
            e->getDest()->setVisited(true);
        }
    }
    cout << "The pair(s) of stations that require the most amount of trains are: \n";
    for(auto it = final.begin(); it != final.end(); it++) {
        cout << it->first.getName() << " and " << it->second.getName() << '\n';
    }
     */
}
void TrainManager::maxFlowOfTrains() {
    auto stations_input = getStationsFromUser();
    Vertex* s = stations_input.first;
    Vertex* t = stations_input.second;
    if (s == nullptr || t == nullptr || s == t){
        cout << "Invalid station!\n";
        return;
    }
    unsigned int max_flow = trainNetwork.edmondsKarp(s,t);
    cout << "The maximum number of trains which can travel between station "
        << s->getStation().getName() << " and station " << t->getStation().getName() << " is "
        << max_flow << ".\n";
}

pair<Vertex*,Vertex*> TrainManager::getStationsFromUser() {
    cout << "What is the name of the source station?";
    Vertex* source = getStationFromUser();
    if (source == nullptr) return {nullptr, nullptr};
    cout << "What is the name of the target station?";
    Vertex* target = getStationFromUser();
    return {source,target};
}

Vertex *TrainManager::getStationFromUser() {
    string name;
    getline(cin, name);
    if (cin.fail()){
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.clear();
        return nullptr;
    }
    Vertex* station = trainNetwork.findVertexByName(name);
    return station;
}

void TrainManager::calculateMaxFlowWithMinimumCost() {
    auto stations_input = getStationsFromUser();
    Vertex* s = stations_input.first;
    Vertex* t = stations_input.second;
    if (s == nullptr || t == nullptr || s == t) {
        cout << "Invalid station!\n";
        return;
    }

    // don't know what we are supposed to do here
}

void TrainManager::useSubGraph() {
    vector<Edge*> deletedEdges;

    while (true){
        cout << "==============================================================\n"
             << "| 1- Delete a segment                                        |\n"
             << "| 2- Calculate the maximum number of trains which can travel |\n"
             << "|    between two given stations.                             |\n"
             << "| 3- Calculate the top-k most affected stations.             |\n"
             << "| 4- Undo changes to network and go back.                    |\n"
             << "==============================================================\n";

        string choice = getAnswer();
        if (choice == "1"){
            cout << "What is the name of the two stations that the segment connects?\n";
            auto stations_input = getStationsFromUser();
            Vertex* s = stations_input.first;
            Vertex* t = stations_input.second;
            if (s == nullptr || t == nullptr || s == t) {
                cout << "Invalid station!\n";
            }

            Edge* temp = trainNetwork.removeBidirectionalEdge(s,t);
            if (temp == nullptr){
                cout << "Some problem occurred when trying to delete that segment!\n";
            }
            else {
                deletedEdges.push_back(temp);
            }
        }
        else if (choice == "2"){
            maxFlowOfTrains();
        }
        else if (choice == "3"){
            // this requires other features which are not yet implemented
        }
        else if (choice == "4"){
            for (Edge* e : deletedEdges){
                Station s1 = e->getOrig()->getStation();
                Station s2 = e->getDest()->getStation();
                trainNetwork.addBidirectionalEdge(s1,s2,e->getWeight(),e->getService());
                delete e;
            }
            return;
        }
        else{
            cout << "Invalid Input\n";
        }
    }
}

string TrainManager::getAnswer() {
    string answer;
    cin >> answer;
    if (cin.fail()){
        cin.clear();
        answer = "";
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//this is required because the names of the stations have spaces
    return answer;
}

void TrainManager::calculateMaxFlowFromNetworkToSingleStation() {
    cout << "What is the name of the station?\n";
    Vertex* v = getStationFromUser();
    if (v == nullptr) {
        cout << "Invalid Station\n";
        return;
    }

    vector<Vertex*> leafNodes ;
    trainNetwork.BFS(v,leafNodes);


    auto newNode = new Vertex(Station("temp","p","","",""));
    for (Vertex* node : leafNodes){
        Edge* edge = newNode->addEdge(node,INF,"No service");
        edge->setFlow(0);
        cout << "One leaf node is : " << node->getStation().getName()<<"!\n";
    }
    int test = 0;
    for(Edge* e : newNode->getAdj()){
        test++;
    }
    cout << "so we have "<< test << " adjacent edges to the new node\n";
    unsigned int p = trainNetwork.edmondsKarp(newNode,v);
    cout << "The maximum number of trains that can simultaneously arrive at station "<< v->getStation().getName()<<
        " is " << p << "!\n";

    for (Edge* e : newNode->getAdj()){
        newNode->removeEdge(e->getDest()->getStation());
    }
    delete newNode;


    //this part is for comparison, meaning its temporary
    unsigned int comparison = 0;
    for (Edge* e : v->getAdj()){
        comparison+= e->getWeight();
    }
    cout << "For comparison, this is the sum of the capacity of every adjacent segment to station "<<
        v->getStation().getName()<< ": " << comparison << ".\n";
}





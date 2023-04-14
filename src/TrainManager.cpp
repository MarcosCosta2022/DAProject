//
// Created by marco on 15/03/2023.
//
#include "TrainManager.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <climits>
#include "Network.h"
using namespace std;

TrainManager::TrainManager() {
    LoadStations();
    LoadNetworks();
}

void TrainManager::LoadStations() {
    string name, district, municipality, township, line , s;
    ifstream in; in.open("../resources/stations2.csv");
    if(!in) cerr << "Could not open the file!" << endl;
    getline(in,s);
    while(getline(in,s)) {
        istringstream iss(s);

        getline(iss, name, ',');
        getline(iss, district, ',');
        getline(iss, municipality, ',');

        if (iss.peek() == '"') {
            getline(iss, township, '"');
            getline(iss, township, '"');
        } else {
            getline(iss, township, ',');
        }
        getline(iss, line, ',');
        getline(iss, line, '\n');

        Station a = Station(name,district,municipality,township,line);
        auto it = stations.find(name);
        if(it==stations.end()){
            stations.emplace(name,a);
            trainNetwork.addVertex(a);
        }
    }
}

void TrainManager::LoadNetworks() {
    int cap;
    string sA, sB, serv, line;
    double w = 0;
    ifstream in; in.open("../resources/network2.csv");
    if(!in) cerr << "Could not open the file! " << endl;
    getline(in, line);
    while(getline(in,line)) {
        istringstream iss(line);
        getline(iss, sA, ','); getline(iss, sB, ',');
        iss >> cap; iss.ignore(1); getline(iss, serv, ',');
        Network a = Network(sA,sB,cap,serv);
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
    vector<pair<Vertex*,Vertex*>>& res = pairsOfStationsWithBiggestMaxFlow;
    if (!res.empty()){
        max = trainNetwork.edmondsKarp(res[0].first,res[0].second);
    }
    else{
        cout << "Calculating...\n";
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
    }
    cout << "The greatest maximum number of trains that can travel simultaneously between stations is "<< max << " and the pairs of stations are:\n";
    for (auto& p : res){
        cout << p.first->getStation().getName() << " and " << p.second->getStation().getName() << '\n';
    }
}

template<typename K, typename V>
struct value_comparator {
    bool operator()(const pair<K, V>& a, const pair<K, V>& b) const {
        return a.second > b.second;
    }
};

void TrainManager::top_municipalities() {
    cout << "How many municipalities you want?";
    int k;
    cin >> k;
    if (top_mun.empty()){
        cout << "Calculating...\n";
        for (int i = 0; i < trainNetwork.getNumVertex(); i++) {
            auto it = top_mun.find(trainNetwork.getVertexSet()[i]->getStation().getMunicipality());
            if (it != top_mun.end()) top_mun.emplace(trainNetwork.getVertexSet()[i]->getStation().getMunicipality(), 0);
        }
        for (int i = 0; i < trainNetwork.getNumVertex(); i++) {
            for (int j = i+1; j < trainNetwork.getNumVertex(); j++) {
                unsigned long temp = trainNetwork.edmondsKarp(trainNetwork.getVertexSet()[i],trainNetwork.getVertexSet()[j]);
                top_mun[trainNetwork.getVertexSet()[i]->getStation().getMunicipality()] += temp;
                top_mun[trainNetwork.getVertexSet()[j]->getStation().getMunicipality()] += temp;
            }
        }
    }
    vector<pair<string,unsigned long>> v(top_mun.begin(),top_mun.end());
    sort(v.begin(), v.end(), value_comparator<string,unsigned long>());
    cout<<"The top-" << k << " municipalities are: \n";
    int i = 0;
    while(i<k && i < v.size()) {
        cout << v[i].first << " with " << v[i].second<< ";\n";
        i++;
    }
}

void TrainManager::top_districts() {
    cout << "How many districts you want?";
    int k;
    cin >> k;
    if (top_dis.empty()){
        cout << "Calculating...\n";
        for (int i = 0; i < trainNetwork.getNumVertex(); i++) {
            auto it = top_dis.find(trainNetwork.getVertexSet()[i]->getStation().getDistrict());
            if (it != top_dis.end()) top_dis.emplace(trainNetwork.getVertexSet()[i]->getStation().getDistrict(), 0);
        }
        for (int i = 0; i < trainNetwork.getNumVertex(); i++) {
            for (int j = i+1; j < trainNetwork.getNumVertex(); j++) {
                unsigned long temp = trainNetwork.edmondsKarp(trainNetwork.getVertexSet()[i],trainNetwork.getVertexSet()[j]);
                top_dis[trainNetwork.getVertexSet()[i]->getStation().getDistrict()] += temp;
                top_dis[trainNetwork.getVertexSet()[j]->getStation().getDistrict()] += temp;
            }
        }
    }
    vector<pair<string,unsigned long>> v(top_dis.begin(),top_dis.end());
    sort(v.begin(), v.end(), value_comparator<string,unsigned long>());
    cout<<"The top " << k << " districts are: \n";
    int i = 0;
    while(i < k && i < v.size()) {
        cout << v[i].first << " with " << v[i].second<< ";\n";
        i++;
    }
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
    cout.clear();
    cout << endl;
    cout << "The maximum number of trains which can travel between station "
        << s->getStation().getName() << " and station " << t->getStation().getName() << " is "
        << max_flow << "." << endl;
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
template<typename K, typename V>
struct value_comparator2 {
    bool operator()(const pair<K, V>& a, const pair<K, V>& b) const {
        if(a.second==b.second) return a.first < b.first;
        return a.second > b.second;
    }
};

void TrainManager::calculateMaxFlowWithMinimumCost() {
    auto stations_input = getStationsFromUser();
    Vertex* s = stations_input.first;
    Vertex* t = stations_input.second;
    if (s == nullptr || t == nullptr || s == t) {
        cout << "Invalid station!\n";
        return;
    }

    unsigned long res = trainNetwork.maxFlowAfterPrim(s,t);
    cout << "The maximum amount of trains which can go from station " << s->getStation().getName() << " and " << t->getStation().getName() << " is "<<res <<".\n";
}

void TrainManager::useSubGraph() {
    vector<Edge> deletedEdges;

    while (true){
        cout << "==============================================================\n"
             << "| 1- Delete a segment                                        |\n"
             << "| 2- Calculate the maximum number of trains which can travel |\n"
             << "|    between two given stations.                             |\n"
             << "| 3- Calculate the top-k most affected stations per segment. |\n"
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

            auto temp = trainNetwork.removeBidirectionalEdge(s,t);
            if (!temp.first){
                cout << "Some problem occurred when trying to delete that segment!\n";
            }
            else {
                deletedEdges.push_back(temp.second);
            }
        }
        else if (choice == "2"){
            maxFlowOfTrains();
        }
        else if (choice == "3"){
            cout << "How many stations per segment?(k)\n";
            int k;
            cin >> k;
            if (cin.fail()){
                cin.clear();
                k = 0;
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            if (k < 1){
                cout << "\nInvalid k\n";
                continue;
            }

            for (Edge& e : deletedEdges){
                Station s1 = e.getOrig()->getStation();
                Station s2 = e.getDest()->getStation();
                trainNetwork.addBidirectionalEdge(s1,s2,e.getWeight(),e.getService());
            }
            vector<Vertex*> tempVerteces;
            for (Edge& e : deletedEdges){
                tempVerteces.clear();
                for (Vertex* v : trainNetwork.getVertexSet()){
                    if (v->getStation().getLine() == e.getOrig()->getStation().getLine()){
                        auto p = getMaxFlowToSingleStation(v);
                        v->setIndegree(p);
                    }
                }
                auto temp = trainNetwork.removeBidirectionalEdge(e.getOrig(),e.getDest());
                for (Vertex* v : trainNetwork.getVertexSet()){
                    if (v->getStation().getLine() == e.getOrig()->getStation().getLine()){
                        auto p = getMaxFlowToSingleStation(v);
                        int tempDiff  = p-v->getIndegree();
                        if (tempDiff < 0 ) tempDiff *= -1;
                        v->setIndegree(tempDiff);
                        if (v->getIndegree() != 0) tempVerteces.push_back(v);
                    }
                }
                Station s1 = e.getOrig()->getStation();
                Station s2 = e.getDest()->getStation();
                trainNetwork.addBidirectionalEdge(s1,s2,e.getWeight(),e.getService());
                sort(tempVerteces.begin(),tempVerteces.end(),[](Vertex* a , Vertex* b){ return a->getIndegree()>b->getIndegree();});
                cout << "The stations that were most affected from removing segment between stations "<< e.getOrig()->getStation().getName() << " and " << e.getDest()->getStation().getName() << " are:\n";
                for (int i = 0 ; (i < k) && (i <tempVerteces.size());i++){
                   cout << "- " << tempVerteces[i]->getStation().getName() << "\n";
                }
                cout << "\n";
            }
            for (Edge& e : deletedEdges){
                trainNetwork.removeBidirectionalEdge(e.getOrig(),e.getDest());
            }
        }
        else if (choice == "4"){
            for (Edge& e : deletedEdges){
                Station s1 = e.getOrig()->getStation();
                Station s2 = e.getDest()->getStation();
                trainNetwork.addBidirectionalEdge(s1,s2,e.getWeight(),e.getService());
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

    unsigned int p = getMaxFlowToSingleStation(v);
    cout << "The maximum number of trains that can simultaneously arrive at station "<< v->getStation().getName()<<
        " is " << p << "!\n";


    //this part is for comparison, meaning its temporary
    unsigned int comparison = 0;
    for (Edge* e : v->getAdj()){
        comparison+= e->getWeight();
    }
    cout << "For comparison, this is the sum of the capacity of every adjacent segment to station "<<
        v->getStation().getName()<< ": " << comparison << ".\n";
}

unsigned long TrainManager::getMaxFlowToSingleStation(Vertex * v) {
    vector<Vertex*> leafNodes ;
    trainNetwork.BFS(v,leafNodes);
    if (leafNodes.empty()){
        return 0;
    }

    Station newStation ("temp","p","","",leafNodes[0]->getStation().getLine());
    trainNetwork.addVertex(newStation);

    for (Vertex* node : leafNodes){
        Station ml = node->getStation();
        trainNetwork.addEdge(newStation,ml,INT_MAX,"NO SERVICE");
    }

    Vertex* newVertex = trainNetwork.findVertex(newStation);
    unsigned long p = trainNetwork.edmondsKarp(newVertex,v);
    trainNetwork.removeVertex(newStation);
    return p;
}





//
// Created by marco on 15/03/2023.
//

#ifndef PROJECT_TRAINMANAGER_H
#define PROJECT_TRAINMANAGER_H

#include "../data_structures/Graph.h"

class TrainManager {
public:
    TrainManager();
    void LoadStations();
    void LoadNetworks();
private:
    Graph trainNetwork;




};

#endif //PROJECT_TRAINMANAGER_H

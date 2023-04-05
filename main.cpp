#include <iostream>
#include "src/TrainManager.h"

using namespace std;
int main() {
    TrainManager h;
    while(true){
        cout << "=============================================================\n"
                <<"| What do you want to do?                                   |\n"
                <<"| 1- Read and parse files in folder resources.              |\n"
                <<"| 2- Calculate the maximum number of trains which can travel|\n"
                <<"|    between two given stations.                            |\n"
                <<"| 3- Calculate the pair of stations which require the most  |\n"
                <<"|    amount of trains.                                      |\n"
                <<"| 4- Top-k municipalities with more transportation needs.   |\n"
                <<"| 5- Maximum number of trains that can simultaneously arrive|\n"
                <<"|    at a given station.                                    |\n"
                <<"| 6- Calculate the maximum amount of trains that can        |\n"
                <<"|    simultaneously travel between two given stations with  |\n"
                <<"|    minimum cost for the company.                          |\n"
                <<"| 7- Use a network of reduced connectivity.                 |\n"
                <<"| 8- Exit                                                   |\n"
                <<"=============================================================\n";
        int option;
        cin >> option;
        if (cin.fail()){
            cin.clear();
            option = 0;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(option){
            case 1:
                h.LoadNetworks();
                h.LoadStations();
                break;
            case 2:h.maxFlowOfTrains();break;
            case 5: h.calculateMaxFlowFromNetworkToSingleStation(); break;
            case 6: h.calculateMaxFlowWithMinimumCost();break;
            case 7: h.useSubGraph();break;
            case 9: return 0;
            default: cout <<"INVALID INPUT\n"; break;
        }
    }
}

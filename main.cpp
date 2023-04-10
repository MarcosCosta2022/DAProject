#include <iostream>
#include "src/TrainManager.h"

using namespace std;
int main() {
    TrainManager h;
    string check;
    while(true){
        cout << "==========================================================================================\n"
                <<"| What do you want to do?                                                                |\n"
                <<"| 1- Read and parse files in folder resources.                                           |\n"
                <<"| 2- Calculate the maximum number of trains which can travel between two given stations. |\n"
                <<"| 3- Calculate the pair of stations which require the most amount of trains.             |\n"
                <<"| 4- Top-k municipalities/districts with more transportation needs.                      |\n"
                <<"| 5- Maximum number of trains that can simultaneously arrive at a given station.         |\n"
                <<"| 6- Calculate the maximum amount of trains that can simultaneously travel between two   |\n"
                <<"|    given stations with minimum cost for the company.                                   |\n"
                <<"| 7- Use a network of reduced connectivity.                                              |\n"
                <<"| 8- Exit                                                                                |\n"
                <<"==========================================================================================\n";
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
            case 2: h.maxFlowOfTrains();break;
            case 3: h.stations_most_amount_trains(); break;
            case 4:
                cout << "Do you want to see the municipalities or the districts? ";
                cin >> check;
                if(check == "municipalities"){
                    h.top_municipalities();
                }
                else if(check == "districts"){
                    h.top_districts();
                }
                break;
            case 5: h.calculateMaxFlowFromNetworkToSingleStation(); break;
            case 6: h.calculateMaxFlowWithMinimumCost();break;
            case 7: h.useSubGraph();break;
            case 8: return 0;
            default: cout <<"INVALID INPUT\n"; break;
        }
    }
}

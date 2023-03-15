#include <iostream>
#include "src/TrainManager.h"

using namespace std;
int main() {
    TrainManager h;
    while(true){
        printf("============================================================="
               "| What do u want to do?                                     |\n"
               "| 1- Read and parse files in folder resources.              |\n"
               "| 2- Calculate the maximum number of trains which can travel|\n"
               "|    between two given stations.                            |\n"
               "| 3- Calculate the pair of stations which require the most  |\n"
               "|    amount of trains.                                      |\n"
               "| 4- Top-k municipalities with more transportation needs    |\n"
               "| 5- Maximum number of trains that can simultaneously arrive|\n"
               "|    at a given station                                     |\n"
               "| 6- Calculate the maximum amount of trains that can        |\n"
               "|    simultaneously travel between two given stations with  |\n"
               "|    minimum cost for the company                           |\n"
               "| 7- Calculate the maximum number of trains that can        |\n"
               "     simultaneously travel between two specific stations in |\n"
               "     a network of reduced connectivity.                     |\n"
               "  8- Top-k most affected stations for each segment failure. |\n"
               "  8- Top-k most affected stations for each segment failure. |\n"
               "| 9- Exit                                                   |\n"
               "=============================================================\n");
        int option;
        cin >> option;
        if (cin.fail()){
            cin.clear();
            option = 0;
        }
        switch(option){
            case 9:
                return 0;
            default:
                printf("INVALID INPUT\n");
                break;
        }
    }
}

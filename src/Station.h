//
// Created by marco on 15/03/2023.
//

#ifndef PROJECT_STATION_H
#define PROJECT_STATION_H
#include <string>

class Station {
public:
    Station();
    Station(std::string C1, std::string C2, std::string C3, std::string C4, std::string C5);

    std::string getC1();
    std::string getC2();
    std::string getC3();
    std::string getC4();
    std::string getC5();

    std::string setC1(std::string cC1);
    std::string setC2(std::string cC2);
    std::string setC3(std::string cC3);
    std::string setC4(std::string cC4);
    std::string setC5(std::string cC5);

private:
    std::string c1;
    std::string c2;
    std::string c3;
    std::string c4;
    std::string c5;

};


#endif //PROJECT_STATION_H

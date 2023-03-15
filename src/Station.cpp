//
// Created by marco on 15/03/2023.
//

#include "Station.h"
using namespace std;

Station::Station(std::string C1, std::string C2, std::string C3, std::string C4, std::string C5) {
    c1 = C1;
    c2 = C2;
    c3 = C3;
    c4 = C4;
    c5 = C5;
}

string Station::getC1() {
    return c1;
}

string Station::getC2() {
    return c2;
}

string Station::getC3() {
    return c3;
}

string Station::getC4() {
    return c4;
}

string Station::getC5() {
    return c5;
}

string Station::setC1(std::string cC1) {
    c1 = cC1;
}

string Station::setC2(std::string cC2) {
    c2 = cC2;
}

string Station::setC3(std::string cC3) {
    c3 = cC3;
}

string Station::setC4(std::string cC4) {
    c4 = cC4;
}

string Station::setC5(std::string cC5) {
    c5 = cC5;
}
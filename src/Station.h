//
// Created by marco on 15/03/2023.
//

#ifndef PROJECT_STATION_H
#define PROJECT_STATION_H
#include <string>



class Station {
public:
    Station();
    Station(const std::string& name, const std::string& district,const std::string& municipality,
                     const std::string& township, const std::string& line);

    std::string getName() const;
    std::string getDistrict() const;
    std::string getMunicipality() const;
    std::string getTownship() const ;
    std::string getLine() const;

    void setName(const std::string& name);
    void setDistrict(const std::string& district);
    void setMunicipality(const std::string& municipality);
    void setTownship(const std::string& township);
    void setLine(const std::string& line);

private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;

};


#endif //PROJECT_STATION_H

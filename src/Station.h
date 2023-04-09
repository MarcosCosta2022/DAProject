//
// Created by marco on 15/03/2023.
//

#ifndef PROJECT_STATION_H
#define PROJECT_STATION_H
#include <string>



class Station {
public:
    /**
     * Constructs a new Station object with default values.
     * This method has a time complexity of O(1).
     */
    Station();
    /**
     * This constructor initializes a new Station object with the given attributes such as name, district,
     * municipality, township, and line.
     * This method has a time complexity of O(1).
     * @param name The name of the station.
     * @param district The district the station is located in.
     * @param municipality The municipality the station is located in.
     * @param township The township the station is located in.
     * @param line The transit line the station is a part of.
     */
    Station(const std::string& name, const std::string& district,const std::string& municipality,
                     const std::string& township, const std::string& line);
    /**
     * Gets the name of the station.
     * This method has a time complexity of O(1).
     * @return The name of the Station object.
     */
    std::string getName() const;
    /**
     * Gets the district of the station.
     * This method has a time complexity of O(1).
     * @return The district of the Station object.
     */
    std::string getDistrict() const;
    /**
     * Gets the municipality of the station.
     * This method has a time complexity of O(1).
     * @return The municipality of the Station object.
     */
    std::string getMunicipality() const;
    /**
     * Gets the township of the station.
     * This method has a time complexity of O(1).
     * @return The township of the Station object.
     */
    std::string getTownship() const;
    /**
     * Gets the line of the station.
     * This method has a time complexity of O(1).
     * @return The line of the Station object.
     */
    std::string getLine() const;

    /**
     * Sets the name of the station.
     * This method has a time complexity of O(1).
     * @param name The new name of the Station object.
     */
    void setName(const std::string& name);
    /**
     * This method sets the district of the Station object to the given district.
     * This method has a time complexity of O(1).
     * @param district The new district of the Station object.
     */
    void setDistrict(const std::string& district);
    /**
     * This method sets the municipality of the Station object to the given municipality.
     * This method has a time complexity of O(1).
     * @param municipality The new municipality of the Station object.
     */
    void setMunicipality(const std::string& municipality);
    /**
     * This method sets the township of the Station object to the given township.
     * This method has a time complexity of O(1).
     * @param township The new township of the Station object.
     */
    void setTownship(const std::string& township);
    /**
     * Sets the line of the station.
     * This method has a time complexity of O(1).
     * @param line The new line of the Station object.
     */
    void setLine(const std::string& line);
    /**
     * Check whether this Station is equal to another Station.
     * The comparison is made based on the equality of the name, district, municipality,
     * township, and line of the two Station objects.
     * @param a The Station object to compare with.
     * @return true if the two Station objects are equal, false otherwise.
     */
    bool operator ==(Station& a) const;

private:
    std::string name;
    std::string district;
    std::string municipality;
    std::string township;
    std::string line;

};


#endif //PROJECT_STATION_H

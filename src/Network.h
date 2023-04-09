//
// Created by marco on 15/03/2023.
//

#ifndef PROJECT_NETWORK_H
#define PROJECT_NETWORK_H

#include <string>

using namespace std;

class Network {

public:
    /**
     * Constructs a new network object with the given station names, capacity, and service.
     * Time complexity of O(1).
     * @param StationA The name of the first station in the network.
     * @param StationB The name of the second station in the network.
     * @param capacity The capacity of the network.
     * @param service The service type of the network.
     */
    Network(std::string stationA, std::string stationB, int capacity, std::string service);
private:
    std::string stationA;
public:
    /**
     * This is a getter function, which returns a constant reference to the name of the first station connected by the network.
     * Time complexity of O(1).
     * @return A constant reference to the name of the first station connected by the network.
     */
    const string &getStationA() const;
    /**
     * Sets the name of the first station connected by the network.
     * This method is a setter function.
     * Time complexity of O(1).
     * @param stationA The new name for the first station.
     */
    void setStationA(const string &stationA);
    /**
     * Returns a constant reference to the name of the second station connected by the network.
     * This method is a getter function and has a time complexity of O(1).
     * @return A constant reference to the name of the second station connected by the network.
     */
    const string &getStationB() const;
    /**
     * Sets the name of the second station connected by the network.
     * This method is a setter function and has a time complexity of O(1).
     * @param stationB The new name for the second station.
     */
    void setStationB(const string &stationB);
    /**
     * Returns the capacity of the network.
     * This method is a getter function and has a time complexity of O(1).
     * @return The capacity of the network.
     */
    int getCapacity() const;
    /**
     * Sets the capacity of the network.
     * This method is a setter function and has a time complexity of O(1).
     * @param capacity The new capacity of the network.
     */
    void setCapacity(int capacity);
    /**
     * Returns the service type of the network.
     * This method is a getter function and has a time complexity of O(1).
     * @return The service type of the network.
     */
    const string &getService() const;
    /**
     * Sets the service type of the network.
     * This method is a setter function and has a time complexity of O(1).
     * @param service The new service type of the network.
     */
    void setService(const string &service);
    /**
     * Compares two network objects for equality.
     * This operator overload compares the first station, second station, capacity, and service type
     * of the current network object with those of another network object to determine whether they are equal.
     * This method has a time complexity of O(1).
     * @param a The network object to compare to.
     * @return True if the two network objects are equal, false otherwise.
     */
    bool operator==(const Network& a) const;
private:
    std::string stationB;
    int capacity;
    std::string service;
};


#endif //PROJECT_NETWORK_H

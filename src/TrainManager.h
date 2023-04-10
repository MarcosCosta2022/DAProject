//
// Created by marco on 15/03/2023.
//

#ifndef PROJECT_TRAINMANAGER_H
#define PROJECT_TRAINMANAGER_H

#include <unordered_map>
#include <map>
#include "../data_structures/Graph.h"

class MyHashFunction {
public:
    size_t operator()(const Network& p) const
    {
        return p.getStationA().length() + p.getStationB().length() + p.getService().length() + p.getCapacity();
    }
};

class TrainManager {
public:
    /**
     * Constructs a TrainManager object and loads stations and networks data.
     * The constructor loads stations and networks data from their respective data files and
     * initializes the TrainManager object with them.
     */
    TrainManager();
    /**
     * Loads station data from a file and initializes Station objects.
     * The method reads station data from a CSV file and initializes Station objects with the data.
     * The Station objects are then added to the `stations` map and the `trainNetwork` graph as vertices.
     * This method assumes the station data file is located in the `../resources` directory and
     * named `stations.csv`.
     * The time complexity is O(n), where n is the number of stations in the file.
     */
    void LoadStations();
    /**
     * Loads the train network connections from the "network.csv" file and creates a bidirectional edge
     * between the two stations, using the capacity and service as edge weights.
     * O(n * log n), where n is the number of network connections in the file. This is
     * because we are inserting each connection into a map, which has a logarithmic time
     * complexity for insertions. Since we are doing this n times, the overall time
     * complexity is O(n * log n).
     */
    void LoadNetworks();
    /**
     * Calculates the maximum number of trains that can travel between two stations based on the current network.
     * Asks the user to input the source and target stations.
     * Uses the Edmonds-Karp algorithm to calculate the maximum flow between the two stations.
     * Outputs the maximum flow to the console.
     * Time complexity is O(|V||E|²)
     */
    void maxFlowOfTrains();
    /**
     * This method prompts the user for the name of a station and calculates the maximum
     * number of trains that can simultaneously arrive at that station.
     * The method uses the Ford-Fulkerson algorithm to compute the maximum flow from the
     * source node (the "network" vertex) to the given station node (the "single" vertex).
     * If the given station name is invalid, the method outputs an error message.
     *
     * Time complexity: O(V*E^2) for the Ford-Fulkerson algorithm (where V is the number of vertices
     * in the graph and E is the number of edges).
     */
    void calculateMaxFlowFromNetworkToSingleStation();
    /**
     * Finds the pairs of stations that have the greatest maximum flow of trains between them.
     * The function first tries to find the maximum flow between the stations already saved in the
     * `pairsOfStationsWithBiggestMaxFlow` attribute. If it is empty, it will calculate the maximum flow
     * between all pairs of stations and update the attribute accordingly. The function prints the maximum
     * flow found and the names of the stations in the pairs with the biggest maximum flow.
     * Time complexity: O(n^3), where n is the number of stations.
     */
    void stations_most_amount_trains();
    /**
     * Calculates the maximum flow with minimum cost between two user-input stations using the network's current edge costs.
     * Uses the Bellman-Ford algorithm to find the cheapest path and the Ford-Fulkerson algorithm to calculate the maximum flow.
     * The edge costs are assumed to be non-negative.
     * If the input stations are invalid, the function will print an error message and return.
     */
    void calculateMaxFlowWithMinimumCost();
    /**
     * Removes a segment from the train network and allows the user to perform various operations
     * on the modified network, such as calculating the maximum number of trains that can travel between two
     * given stations, calculating the top-k most affected stations per segment, and undoing changes to the network.
     * The worst-case time complexity of this function is O(N*M*log(N)), where N is the number of vertices in the graph and M is the number of edges in the graph. This is because the function performs operations such as removing edges from the graph, calculating maximum flow, and sorting vertices, all of which have time complexity proportional to N and M.
     */
    void useSubGraph();
    void top_municipalities();
    void top_districts();

    /**
     * Calculates the maximum flow of trains that can travel to a single station
     * @param v The vertex representing the station to calculate the maximum flow to
     * @return The maximum flow of trains that can travel to the station
     * Time complexity: O((V+E) * E^2), where V is the number of vertices in the train network, E is the number of edges
     */
    unsigned long getMaxFlowToSingleStation(Vertex* v);
    /**
     * Reads a string input from the user and returns it after clearing any input errors.
     * @return A string input from the user.
     * The time complexity of this function is O(n), where n is the length of the input string.
     */
    string getAnswer();
    /**
     * Prompts the user for the name of a station and returns a pointer to the corresponding vertex in the train network.
     * If the user enters an invalid input or there is no vertex with the specified name, returns nullptr.
     * Time complexity: O(|V|), where |V| is the number of vertices in the train network.
     * @return a pointer to the vertex corresponding to the user input or nullptr if the input is invalid or no such vertex exists.
     */
    Vertex* getStationFromUser();
    /**
     * Asks the user for the names of two stations and returns the corresponding vertices.
     * @return A pair of pointers to Vertex objects, representing the source and target stations, respectively.
     * If either station is not found, returns a pair of nullptrs.
     * Time complexity: O(N), where N is the number of vertices in the train network.
     */
    pair<Vertex*,Vertex*> getStationsFromUser();
private:
    Graph trainNetwork;
    unordered_map<std::string,Station> stations;
    unordered_map<Network,double,MyHashFunction> networks;
    vector<pair<Vertex*,Vertex*>> pairsOfStationsWithBiggestMaxFlow;
    map<std::string,unsigned long> top_mun;
    map<std::string, unsigned long> top_dis;


};



#endif //PROJECT_TRAINMANAGER_H

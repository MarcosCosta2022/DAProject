#ifndef PROJECT_VERTEXEDGE_H
#define PROJECT_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "../src/Station.h"
#include "../src/Network.h"

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(Station station1);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    Station getStation() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setStation(Station station2);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, Network w);
    bool removeEdge(Station destStation);

    //friend class MutablePriorityQueue<Vertex>;
protected:
    Station station;                // identifier
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, Network w);

    Vertex * getDest() const;
    Network getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest; // destination vertex
    Network weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};

#endif //PROJECT_VERTEXEDGE_H

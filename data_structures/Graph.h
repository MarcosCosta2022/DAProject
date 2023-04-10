#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
//#include "../data_structures/MutablePriorityQueue.h"

#include "VertexEdge.h"

class Graph {
public:
    ~Graph();

    Vertex *findVertex(Station &station2) const;

    Vertex* findVertexByName(const string& name) const;

    /**
     * Adds a vertex with a given content or info (station2) to a graph (this).
     * @param station2 Vertex to add to graph
     * @return true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Station &station2);

    /**
     * Removes a vertex with a given content or info (station2) to a graph (this).
     * @param station2 Vertex to remove from graph
     * @return true if successful, and false if a vertex with that content doesn't exist.
     */
    bool removeVertex(Station &station2);

    /**
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices, the edge weight (w) and the service(service).
     * @param sourc Source station which the edge comes from
     * @param dest  Destination vertex which the edge point to
     * @param w Weight of the edge
     * @param service Service provided by this segment of the train network
     * @return true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(Station &sourc, Station &dest, int w , const string& service);

    /**
     * Adds 2 edges to a graph (this), given the contents of the source and
     * destination vertices, the edge weight (w) and the service(service).
     * @param sourc Source station which the edge comes from
     * @param dest  Destination vertex which the edge point to
     * @param w Weight of the edge
     * @param service Service provided by this segment of the train network
     * @return true if successful, and false if the source or destination vertex does not exist.
     */
    bool addBidirectionalEdge(Station &sourc, Station &dest, int  w , const string& service);

    /**
     * @return returns the number of vertices
     */
    int getNumVertex() const;

    /**
     * @return returns a set with all vertices
     */
    std::vector<Vertex *> getVertexSet() const;

    void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);

    /**
     * Finds a path between node s and t, updating the values of path inside the nodes
     *
     * Complexity : O(V+E) where V and E stands for the number of vertices and edges in the graph respectively.
     * @param s The first node of the path, source node
     * @param t The last node of the path, target node
     * @return Returns true if successful, false if no path exists between node s and t
     */
    bool findAugmentingPath(Vertex *s, Vertex *t);

    /**
     * Goes through the path indicated by the path attribute inside vertex to find the minimum value of the
     * residual(capacity - flow) of every vertex in the path.
     *
     * Complexity : O(V) where V is the number of vertices in the graph
     * @param s The start of the path , source node
     * @param t The end of the path , source node
     * @return The minimum value of the residual between the nodes in the path
     */
    double findMinResidualAlongPath(Vertex *s, Vertex *t);

    /**
     * Goes through the path indicated by the path attribute inside vertex and adds to the values of flow of every
     * vertex in that path the value f
     *
     * Complexity : O(V) where V is the number of vertices in the graph
     * @param s The source node of the path
     * @param t The target node of the path
     * @param f The value to add to the flow of the nodes in the path
     */
    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);

    /**
     * Applies the algorithm Edmonds-Karp to find the maximum flow from node s to node t
     *
     * Complexity : O(VE^2)
     * @param s Source node
     * @param t Target node
     * @return The maximum flow from s to t
     */
    unsigned int edmondsKarp(Vertex* s , Vertex* t);

    /**
     * Removes the edge in a undirected graph which connects nodes s and t
     * @param s One of the nodes which the edges connects to
     * @param t The other node which the edge connects to
     * @return A pair whose first elements is true if there exists an edge between s and t, false otherwise, and the
     * second element is a copy of the edge that connects s and t, in case it exists
     */
    pair<bool,Edge> removeBidirectionalEdge(Vertex* s , Vertex* t);

    /**
     * Performs a Breath-First Search to find the leaf nodes of the tree with root node n of an MST graph considering
     * every edge has the same weight 1.
     *
     * Complexity : O(V + E)
     * @param n Root node
     * @param v Empty vector which will contain the leaf nodes upon exiting
     */
    void BFS(Vertex *n, vector<Vertex*>& v);

    /**
     * Performs the prims algorithm
     * @param s Source vertex
     */
    void prims(Vertex* s);

    /**
     * Finds the maximum flow after executing the prims algorithm
     * @param s
     * @param t
     * @return
     */
    unsigned long maxFlowAfterPrim(Vertex* s , Vertex*t);



protected:
    std::vector<Vertex *> vertexSet;    // vertex set


    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //PROJECT_GRAPH_H

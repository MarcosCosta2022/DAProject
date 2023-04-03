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
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(Station &station2) const;

    Vertex* findVertexByName(const string& name) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Station &station2);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(Station &sourc, Station &dest, int w , const string& service);
    bool addBidirectionalEdge(Station &sourc, Station &dest, int  w , const string& service);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;

    void testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual);
    bool findAugmentingPath(Vertex *s, Vertex *t);
    double findMinResidualAlongPath(Vertex *s, Vertex *t);
    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);
    unsigned int edmondsKarp(Vertex* s , Vertex* t);
protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    //Será importante?? int findVertexIdx(const int &id) const; // prob not
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif //PROJECT_GRAPH_H

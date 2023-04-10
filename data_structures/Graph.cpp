#include "Graph.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(Station &station2) const {
    for (auto v : vertexSet)
        if (v->getStation() == station2)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
/*
int Graph::findVertexIdx(co &station2) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getStation() == station2)
            return i;
    return -1;
}
*/
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(Station &station2) {
    if (findVertex(station2) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(station2));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(Station &sourc, Station &dest, int w , const string& service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w ,service);
    return true;
}

bool Graph::addBidirectionalEdge(Station &sourc, Station &dest, int w, const string& service) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w ,service);
    auto e2 = v2->addEdge(v1, w , service);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

Vertex *Graph::findVertexByName(const string &name) const {
    for (auto v : vertexSet)
        if (v->getStation().getName() ==name)
            return v;
    return nullptr;
}

void Graph::testAndVisit(std::queue< Vertex*> &q, Edge *e, Vertex *w, double residual) {
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

bool Graph::findAugmentingPath(Vertex *s, Vertex *t) {
    for(auto v : vertexSet) {
        v->setVisited(false);
    }
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

double Graph::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    double f = INF;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}

void Graph::augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

unsigned int Graph::edmondsKarp(Vertex* s , Vertex* t) {
    if (s->getStation().getLine() != t->getStation().getLine()) return 0;
    for (auto v : vertexSet) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }

    // Loop to find augmentation paths
    while( findAugmentingPath(s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
    unsigned int max_flow = 0;
    for(Edge* e : s->getAdj()){
        max_flow+=e->getFlow();
    }
    return max_flow;
}

pair<bool,Edge> Graph::removeBidirectionalEdge(Vertex *s, Vertex *t) {
    Edge* res = nullptr;
    for (Edge* e : s->getAdj()){
        if (e->getDest() == t){
            res = e;
        }
    }
    if (res == nullptr) return {false,{nullptr,nullptr,0,""}};
    Edge temp = *res;
    if (s->removeEdge(t->getStation()) && t->removeEdge(s->getStation()))
        return {true,temp};
    else return {false,{nullptr,nullptr,0,""}};
}
void Graph::BFS(Vertex *n, vector<Vertex*>& v) {
    for (Vertex* l : vertexSet){
        l->setVisited(false);
    }
    queue<Vertex*> q;
    q.push(n);
    n->setVisited(true);
    while(!q.empty()){
        auto p = q.front();
        q.pop();
        bool check = true;
        for (Edge* e : p->getAdj()){
            Vertex* d = e->getDest();
            if (!d->isVisited() && e->getService() == "STANDARD"){
                d->setVisited(true);
                check = false;
                q.push(d);
            }
        }
        if (check){
            v.push_back(p);
        }
    }
}

bool Graph::removeVertex(Station& station2) {
    bool c =false;
    auto i = vertexSet.begin();
    for (;i!=vertexSet.end();i++){
        if ((*i)->getStation() == station2){
            c = true;
            break;
        }
    }
    if (!c) return false;
    auto moi = *i;
    vertexSet.erase(i);
    moi->removeAllEdges();
    delete moi;
    return true;
}
pair<double,double> Graph::findMinResidualAlongPath2(Vertex *s, Vertex *t) {
    double f = INF;
    double c = 0;
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
            if(e->getService() == "STANDARD") c+=2;
            else if(e->getService() == "ALFA PENDULAR") c+=4;
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
            if(e->getService() == "STANDARD") c+=2;
            else if(e->getService() == "ALFA PENDULAR") c+=4;
        }
    }
    return make_pair(f,c);
}



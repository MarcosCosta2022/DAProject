#include <climits>
#include "Graph.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}


Vertex * Graph::findVertex(Station &station2) const {
    for (auto v : vertexSet)
        if (v->getStation() == station2)
            return v;
    return nullptr;
}

bool Graph::addVertex(Station &station2) {
    if (findVertex(station2) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(station2));
    return true;
}

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

bool compare(const Vertex* a , const Vertex* b){
    return a->getDist()> b->getDist();
}

void Graph::prims(Vertex *s) {

    std::priority_queue<Vertex*, std::vector<Vertex*>, decltype(&compare)> p(&compare);
    for (Vertex* v : vertexSet){
        v->setPath(nullptr);
        v->setVisited(false);
        v->setDist(INF);
        p.push(v);
    }
    s->setDist(0);
    p.push(s);
    while(!p.empty()){
        Vertex* node = p.top();
        p.pop();
        node->setVisited(true);
        for (Edge* e : node->getAdj()){
            Vertex* d = e->getDest();
            double temp = e->getService() == "STANDARD" ? 2*e->getWeight():4*e->getWeight();
            if (!d->isVisited() && d->getDist() > temp){
                d->setDist(temp);
                d->setPath(e);
                p.push(d);
            }
        }
    }
}

unsigned long Graph::maxFlowAfterPrim(Vertex *s, Vertex *t) {
    if (s->getStation().getLine() != t->getStation().getLine())return 0;
    prims(s);
    if (t->getPath() == nullptr) return 0;
    unsigned long maximum_flow = INT_MAX;
    Vertex* temp = t;
    while(temp != s){
        Edge* p = temp->getPath();
        temp = p->getOrig();
        if (p->getWeight()<maximum_flow){
            maximum_flow = p->getWeight();
        }
    }
    return maximum_flow;
}




#include "VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(Station station1): station(station1) {}


Edge * Vertex::addEdge(Vertex *d,int w, const string& service) {
    auto newEdge = new Edge(this, d, w,service);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(Station destStation) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getStation() == destStation) {
            it = adj.erase(it);
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getStation() == station) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true;
        }
        else {
            it++;
        }
    }
    return removedEdge;
}



bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

Station Vertex::getStation() const {
    return this->station;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setStation(Station station2) {
    this->station = station2;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::removeAllEdges() {
    while(adj.size() != 0){
        removeEdge(adj[0]->getDest()->getStation());
    }
}


/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, int w , const string& service): orig(orig), dest(dest), weight(w) , service(service){}

Vertex * Edge::getDest() const {
    return this->dest;
}

int Edge::getWeight() const {
    return this->weight;
}

string Edge::getService() const {
    return this->service;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}


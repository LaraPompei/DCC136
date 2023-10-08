#include "Graph.h"

Graph::Graph() {
    // Inicialize membros com valores padrão
    nTrip = 0;
    H = 0;
    N = 0;
    TMax = 0.0f;
}

// Métodos Get
std::vector<Node> Graph::getNodes() const {
    return Nodes;
}

int Graph::getnTrip() const {
    return nTrip;
}

int Graph::getH() const {
    return H;
}

int Graph::getN() const {
    return N;
}

std::list<float> Graph::getTripLength() const {
    return TripLength;
}

float Graph::getTMax() const {
    return TMax;
}

float* Graph::getDist()  {
    return dist;
}

// Métodos Set
void Graph::setNodes(const std::vector<Node>& nodes) {
    Nodes = nodes;
}

void Graph::setnTrip(int trips) {
    nTrip = trips;
}

void Graph::setH(int h) {
    H = h;
}

void Graph::setN(int n) {
    N = n;
}

void Graph::setTripLength(const std::list<float>& lengths) {
    TripLength = lengths;
}

void Graph::setTMax(float tMax) {
    TMax = tMax;
}

void Graph::setDist(float *distances) {
    dist = distances;
}

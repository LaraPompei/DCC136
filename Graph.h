#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <vector>
#include <list>

class Graph {
private:
    std::vector<Node> Nodes;
    int nTrip;
    int H;
    int N;
    std::list<float> TripLength;
    float TMax;
    float *dist;

public:
    Graph(); // Construtor padrão

    // Métodos Get
    std::vector<Node> getNodes() const;
    int getnTrip() const;
    int getH() const;
    int getN() const;
    std::list<float> getTripLength() const;
    float getTMax() const;
    float* getDist() ;

    // Métodos Set
    void setNodes(const std::vector<Node>& nodes);
    void setnTrip(int trips);
    void setH(int h);
    void setN(int n);
    void setTripLength(const std::list<float>& lengths);
    void setTMax(float tMax);
    void setDist(float *distances);
};

#endif

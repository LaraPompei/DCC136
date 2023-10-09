#include "Graph.h"
#include <math.h>

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

float Graph::CalculaDistancia(int i, int j){

if (i == j)
    return 0.0;

else if(i < j)
    return dist[((i + (((j-1)*j)/2)))];

else
    return dist[((j + (((i-1)*i)/2)))];



}

bool Graph::VerificaViabilidadeHotel(Node n, float val, std::vector<Node> hoteis){

for(auto i:hoteis){

if(val - CalculaDistancia(n.getId(),i.getId()) > 0)
    return true;



}

return false;


}


std::list<Node> Graph::OrdenaCandidatos(std::vector <Node> v, Node n){

std::list<Node> Candidatos;
std::copy(v.begin(), v.end(), Candidatos.begin());

for(auto i:Candidatos)
i.setPontos((pow(i.getScore(),2))/(CalculaDistancia(i.getId(), n.getId())));


Candidatos.sort([](const Node &f, const Node &s) { return f.pontos > s.pontos; });



return Candidatos;

}
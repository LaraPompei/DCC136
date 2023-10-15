#include "Node.h"

Node::Node(){
    this->hotel = 0;
    id = 0;
    x = 0;
    y = 0;
    s=0;
    visitado = 0;
}

Node::Node(bool hotel, int nodeId, float posX, float posY, int score){
    this->hotel = hotel;
    id = nodeId;
    x = posX;
    y = posY;
    s=(hotel)?0:score;
    visitado = 0;
}

// Métodos Get
bool Node::getHotel(){
    return hotel;
}

bool Node::getVisitado(){
    return visitado;
}

int Node::getId(){
    return id;
}

float Node::getX(){
    return x;
}

float Node::getY(){
    return y;
}

float Node::getScore(){
    return s;
}

float Node::getRazao(){
    return float(razao);
}

float Node::getDistancia(int Id){
    return distancia[Id];
}

// Métodos Set
void Node::setHotel(bool hotel) {
    this->hotel = hotel;
}

void Node::setVisitado(bool visitado){
    this->visitado = visitado;
}

void Node::setId(int nodeId) {
    id = nodeId;
}

void Node::setX(float posX) {
    x = posX;
}

void Node::setY(float posY) {
    y = posY;
}

void Node::setScore(float score) {
    s = score;
}

void Node::setRazao(float Razao){
    razao = Razao;
}

//Outros metodos
void Node::atualizaDistancia(Node novoNo){
        distancia.push_back(sqrt(pow((novoNo.getX()-x),2)+pow((novoNo.getY()-y),2)));
}

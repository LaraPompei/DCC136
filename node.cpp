#include "Node.h"

Node::Node() {
    // Inicialize membros com valores padrão
  /*  hotel = false;
    id = 0;
    x = 0.0f;
    y = 0.0f;
    s = 0.0f;
    pontos = 0.0f;*/
}

Node::Node(bool isHotel, int nodeId, float posX, float posY, float score) {
    hotel = isHotel;
    id = nodeId;
    x = posX;
    y = posY;
    s = score;
}

// Métodos Get
bool Node::isHotel() const {
    return hotel;
}

int Node::getId() const {
    return id;
}

float Node::getX() const {
    return x;
}

float Node::getY() const {
    return y;
}

float Node::getScore() const {
    return s;
}

float Node::getPontos() const {
    return pontos;
}

// Métodos Set
void Node::setHotel(bool isHotel) {
    hotel = isHotel;
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

void Node::setPontos(float p) {
    pontos = p;
}
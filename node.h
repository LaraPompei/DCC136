#ifndef NODE_H
#define NODE_H

class Node {
public:
    bool hotel;
    int id;
    float x;
    float y;
    float s;
    float pontos;


    Node(); // Construtor padrão
    Node(bool isHotel, int nodeId, float posX, float posY, float size);

    // Métodos Get
    bool isHotel() const;
    int getId() const;
    float getX() const;
    float getY() const;
    float getScore() const;
    float getPontos() const;

    // Métodos Set
    void setHotel(bool isHotel);
    void setId(int nodeId);
    void setX(float posX);
    void setY(float posY);
    void setScore(float score);
    void setPontos(float pontos);
};

#endif

#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
class Node {

    private:
        bool hotel;     //variavel que identifica se o noh eh um hotel
        bool visitado;  //variavel que identifica se o noh ja foi if(hotel)?visitado=0
        int id;         //variavel que identifica a id do noh
        float x;        //posicao do noh no eixo x
        float y;        //posicao do noh no eixo y
        float s;        //qtd de pontos do noh if(hotel)?s=0:s=[H+1...H+N](grafo)
        float razao;    //armazena a razao entre (s^2/distancia) 
        vector<float> distancia; //armazena a distancia do no atual para todos os outros
         
    public:
        Node();
        Node(bool hotel, int nodeId, float posX, float posY, int score);

        // Métodos Get
        bool getHotel();
        bool getVisitado();
        int getId();
        float getX();
        float getY();
        float getScore();
        float getRazao();
        float getDistancia(int Id);

        // Métodos Set
        void setHotel(bool hotel);
        void setVisitado(bool visitado);
        void setId(int nodeId);
        void setX(float posX);
        void setY(float posY);
        void setScore(float score);
        void setRazao(float Razao);
        
        //outros metodos
        void atualizaDistancia(Node novoNo); //calcula distancia do novo no adicionado para o atual
};

#endif

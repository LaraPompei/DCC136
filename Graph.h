#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
using namespace std;
class Graph {
    private:
        //variaveis
        int h;          //numero de hoteis[0,H]
        int n;          //numero de vertices
        int numTrips;   //numero de Trips que se planeja fazer 
        int tamTour;    //tamanho da tour total 
        Node H0;        //Hotel inicial
        Node H1;        //Hotel Final

        //vetores e listas
        vector<Node> Nos;           //vetor que armazena os nos do grafo
        list<float> TamTrip;        //lista que armazena o tamanho de cada Trip
        vector<Node> Solucao;       //vetor que armazena a solucao inicial do grado        
    
    public:
        Graph(); // Construtor padrão

        // Métodos Get
        vector<Node> getNos();
        list<float> getTamTrip();
        int getH();
        int getN();
        int getNumTrips();
        int getTamTour();
        

        // Métodos Set
        void setH(int h);
        void setN(int n);
        void setH0(Node h);
        void setH1(Node h);
        void setNumTrips(int numTrips);
        void setTamTour(int tamTour);
        void setNos(vector<Node>& nos);
        void setTamTrips(float tamTrip);

        // Outros métodos
        float CalculaDistancia(Node n1, Node n2);
        bool VerificaViabilidadeHotel(Node n, float val, std::vector<Node> hoteis);
        vector<Node> calculaSolucaoGreed();
        void ImprimeSolucao(std::vector<Node> vec);
        list<Node> OrdenaCandidatos(Node n);
        void AddNo(Node no);
        void CalculaSolucao();
        bool Comparacao(Node f, Node s);
        
        //metodos da busca local
        void Inserir(float trip);   //seleciona os melhores nos para serem acrescentados na solucao
        void Trocar();              //pega os vertices nao visitados e os inclui na posicao que aumentariam menos o tempo. Se nao for possivel fazer isso, seleciona um no que tenha um score                                     //inferior a ele e ja foi incluido e verifica se sua exclusao faria com que o novo no possa ser incluido
        void Inverter();            //para cada vertice na solucao, testar se inverte-lo com o outro gera uma diminuicao no tempo total da trip
        void MoverMelhor();         //para cada vertice dentro da tour, verificar se muda-lo para a sua melhor posicao eh possivel

};

#endif

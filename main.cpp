#include<iostream>
#include<list>
#include<vector>
#include<fstream>
#include <time.h>
#include <chrono>
#include <math.h>
#include "Graph.h"
#include "Node.h"

using namespace std;
using namespace std::chrono;

/*Graph leitura_instancia(int selecionar){        //Funcao para a leitura das instancias


    ifstream leitor;


    switch (selecionar) // Algumas instâncias escolhidas para testes
    {
        case  0:
            leitor.open("64-45-6-4.ophs");
            break;
        case  1:
            leitor.open("66-55-2-3.ophs");
            break;
        case  2:
            leitor.open("66-125-12-4.ophs");
            break;
        case  3:
            leitor.open("100-100-10-4.ophs");
            break;
        case  4:
            leitor.open("100-120-15-4.ophs");
            break;
        case  5:
            leitor.open("100-200-15-10.ophs");
            break;
        case  6:
            leitor.open("102-35-3-3.ophs");
            break;
        case  7:
            leitor.open("T1-73-5-3.ophs");
            break;
        case  8:
            leitor.open("T3-95-1-2.ophs");
            break;
        case  9:
            leitor.open("100-80-10-6.ophs");
            break;
        default:
            break;
    }

    string linha;
                  
    Graph *g = new Graph;                          

    int i = 0 ;

    //le as duas primeiras linhas
    int aux;
    float aux2;

    leitor >> aux; g->setN(aux); //N+2
    leitor >> aux; g->setH(aux); //H-2
    leitor >> aux; g->setnumTrip(aux); //qtd de Trips que serao feitas

    getline(leitor,linha);
    leitor >> aux2; g->set(aux2); //tamanho da Tour

    getline(leitor,linha);


    list<float> aux3;
    for (int k = 0; k < g->getnTrip(); k++){
        leitor >> aux2;
        aux3.push_back(aux);

    }g->setTripLength(aux3);


    getline(leitor,linha);
    getline(leitor,linha);

    Node z;
    float aux4;
    vector <Node> auxNode;
    leitor >> aux4;
    z.setId(i) ;
    z.setX(aux4);
    leitor >> aux4;
    z.setY(aux4);
    leitor >> aux4;
    z.setScore(int(aux4));
    z.setHotel(true);
    auxNode.push_back(z);
    i++;
    getline(leitor,linha);



    leitor >> aux4;
    z.setId(i) ;
    z.setX(aux4);
    leitor >> aux4;
    z.setY(aux4);
    leitor >> aux4;
    z.setScore(aux4);
    z.setHotel(true);
    auxNode.push_back(z);
    i++;
    getline(leitor,linha);



    for(int k = 0; k < g->getH(); k++){
        z.setId(i) ;
        leitor >> aux4;
        z.setX(aux4);
        leitor >> aux4;
        z.setY(aux4);
        leitor >> aux4;

        z.setScore(aux4);
        z.setHotel(true);
        auxNode.push_back(z);
        i++;
        getline(leitor,linha);
    }

    for(int k = 0; k < g->getN()-2; k++){
        leitor >> aux4;
        z.setId(i);
        z.setX(aux4);
        leitor >> aux4;
        z.setY(aux4);
        leitor >> aux4;
        z.setScore(int(aux4));
        z.setHotel(false);
        auxNode.push_back(z);
        i++;
        getline(leitor,linha);

    }
    g->setNodes(auxNode);

    int k = g->getH()+g->getN();
    float *auxDist = new float [(((k*k)-k)/2)];

    int cont = 0;
    for(int i = 0; i < k; i++){
        for(int j = i+1; j<k; j++){
        
        float val = sqrt(pow((auxNode.at(j).getX()) - (auxNode.at(i).getX()),2) + pow((auxNode.at(j).getY() )- auxNode.at(i).getY(),2));
        
        if (i < j){
            auxDist[((i + (((j-1)*j)/2)))] = val;
        }else{
            auxDist[((j + (((i-1)*i)/2)))] = val;}
            cont++;
        }
    }

    g->setDist(auxDist);
    
    return *g;
}*/

Graph leitura(int selecionar){
    ifstream leitor;


    switch (selecionar) // Algumas instâncias escolhidas para testes
    {
        case  0:
            leitor.open("64-45-6-4.ophs");
            break;
        case  1:
            leitor.open("66-55-2-3.ophs");
            break;
        case  2:
            leitor.open("66-125-12-4.ophs");
            break;
        case  3:
            leitor.open("100-100-10-4.ophs");
            break;
        case  4:
            leitor.open("100-120-15-4.ophs");
            break;
        case  5:
            leitor.open("100-200-15-10.ophs");
            break;
        case  6:
            leitor.open("102-35-3-3.ophs");
            break;
        case  7:
            leitor.open("T1-73-5-3.ophs");
            break;
        case  8:
            leitor.open("T3-95-1-2.ophs");
            break;
        case  9:
            leitor.open("100-80-10-6.ophs");
            break;
        case 10:
            leitor.open("100-80-10-6.ophs");
            break;
        case 11:
            leitor.open("100-80-10-6.ophs");
            break;
        case 12:
            leitor.open("100-80-10-6.ophs");
            break;
        case 13:
            leitor.open("100-80-10-6.ophs");
            break;
        case 14:
            leitor.open("100-80-10-6.ophs");
            break;
        case 15:
            leitor.open("100-80-10-6.ophs");
            break;
        case 16:
            leitor.open("100-80-10-6.ophs");
            break;
        default:
            break;
    }

    string linha;

    Graph *g = new Graph;
    
    //le as primeiras linhas que contem informaçoes a respeito do grafo
    int aux;
    float aux2;

    leitor >> aux; g->setN(aux);        //N
    leitor >> aux; g->setH(aux);        //H
    leitor >> aux; g->setNumTrips(aux);  //qtd de Trips que serao feitas

    getline(leitor,linha);

    leitor >> aux2; g->setTamTour(aux2);       //tamanho da Tour

    getline(leitor,linha);

    //le o tamanho das trips
    for (int k = 0; k < g->getNumTrips(); k++){
        leitor >> aux2;
        g->setTamTrips(aux2); 
    }

    getline(leitor,linha);

    getline(leitor,linha);

    Node noAux;

    for(int k = 0; k < g->getH(); k++){
        leitor >> aux2;
        noAux.setX(aux2);
        leitor >> aux2;
        noAux.setY(aux2);
        leitor >> aux;
        noAux.setScore(int(aux));
        noAux.setHotel(true);
        if(k==0)
            g->setH0(noAux);
        else if(k=1)
           g->setH1(noAux);
        
        g->AddNo(noAux);
        getline(leitor,linha);
    }
    for(int k = 0; k < g->getN(); k++){
        leitor >> aux2;
        noAux.setX(aux2);
        leitor >> aux2;
        noAux.setY(aux2);
        leitor >> aux;
        noAux.setScore(int(aux));
        noAux.setHotel(false);
        g->AddNo(noAux);
        getline(leitor,linha);
    }

    return *g;
}

int main(){


    Graph g = leitura(5); // chama a função para a instância x

/*    cout<<"H:"<<g.getH()<<"\tN:"<<g.getN()<<"\tnumTrips:"<<g.getNumTrips()<<"\ttamTour:"<<g.getTamTour()<<endl;
    for(auto x:g.getTamTrip())
        cout<<x<<"\t";
    cout<<endl;
    for(auto x:g.getNos()){

    cout<<"ID: "<<x.getId()<<" "<<"x: "<<x.getX()<<" "<<"y: "<<x.getY()<<" "<<"s: "<<x.getScore()<<endl;

}*/

    g.CalculaSolucao();
    g.ImprimeSolucao();
}





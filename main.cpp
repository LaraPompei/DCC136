#include<iostream>
#include<list>
#include<vector>
#include<fstream>
#include <time.h>
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;


struct Node
{   bool hotel; // É hotel?
    int id;  // id do nó
    float x; // coordenada x
    float y; // coordenada y
    float s; // Valor da pontuação
};



struct Graph //Estrutura do grafo
{
    
  vector<Node> Nos; //Vetor de nós
  int nTrip;  // N de trips
  int H; // N de hotéis extras
  int N;  // N de nós +2 
  list<float> TripLength; // Lista com o valor máximo de cada trip
  float TMax; // Distância máxima da tour
  float *dist;  // Vetor que armazena a matriz triangular superior ignorando a inferior e a diagonal principal
};

struct Candidato // Estrutura auxiliar
{
Node no; // O nó em si
float score; // Score atribuído pela eurística
};


Graph leitura_instancia(int selecionar){        //Funcao para a leitura das instancias


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


leitor >> g->N;
leitor >> g->H;
leitor >> g->nTrip;

getline(leitor,linha);
leitor >> g->TMax;

getline(leitor,linha);

float aux = 0;

for (int k = 0; k < g->nTrip; k++){
    leitor >> aux;
    g->TripLength.push_back(aux);
}
getline(leitor,linha);
getline(leitor,linha);

Node z;

leitor >> aux;
z.id = i;
z.x = aux;
leitor >> aux;
z.y = aux;
leitor >> aux;
z.s = aux;
z.hotel = true;
g->Nos.push_back(z);
i++;
getline(leitor,linha);

leitor >> aux;
z.id = i;
z.x = aux;
leitor >> aux;
z.y = aux;
leitor >> aux;
z.s = aux;
z.hotel = true;
g->Nos.push_back(z);
i++;
getline(leitor,linha);



for(int k = 0; k < g->H; k++){
leitor >> aux;
z.id = i;
z.x = aux;
leitor >> aux;
z.y = aux;
leitor >> aux;
z.s = aux;
z.hotel = true;
g->Nos.push_back(z);
i++;
getline(leitor,linha);

}






for(int k = 0; k < g->N-2; k++){
leitor >> aux;
z.id = i;
z.x = aux;
leitor >> aux;
z.y = aux;
leitor >> aux;
z.s = aux;
z.hotel = false;
g->Nos.push_back(z);
i++;
getline(leitor,linha);

}


int k = g->H+g->N;
g->dist = new float [(((k*k)-k)/2)];
int cont = 0;
for(int i = 0; i < k; i++){
    for(int j = i+1; j<k; j++){
        
        float val = sqrt(pow((g->Nos.at(j).x) - (g->Nos.at(i).x),2) + pow((g->Nos.at(j).y )- (g->Nos.at(i).y),2));
        
        if (i < j){
        g->dist[((i + (((j-1)*j)/2)))] = val;
        }
        else
        g->dist[((j + (((i-1)*i)/2)))] = val;
    }


}





return *g;


}


float consulta_dist(Graph g, int i, int j){ // Função para consultar no vetor a distância entre o nó i e j
int x, y;
if(i == j){  // A distância de um nó para ele mesmo é zero e isso não é armazenado
    return 0.0;
}
else if(i > j){ // Caso i > j trocamos 
    x = j;
    y = i;

}
else{
    x =i;
    y =j;
}
return g.dist[((x + (((y-1)*y)/2)))]; // A função vai retornar o valor desejado

}

list <Candidato> Rank(Graph g, vector<Node> v, Node n){ // Função para ranquear os candidatos 

list <Candidato> *candidatos = new list<Candidato>;
for (auto u:v){
Candidato c; 
c.no = u;
if (consulta_dist(g,u.id,n.id)>0){
c.score = (pow(u.s,2))/(consulta_dist(g,u.id,n.id)); // euristica utilizada para teste: s²/distancia(i,j)
candidatos->push_back(c);
}
}
candidatos->sort([](const Candidato &f, const Candidato &s) { return f.score > s.score; }); // Ordena do maior para o menor
return *candidatos;

}

void Solucao(Graph g){
Node aux = g.Nos.at(0);
vector<Node> naux = g.Nos;
list <Candidato> l = Rank(g, naux,aux);
list<float> trips = g.TripLength;

for(auto x:l){

cout<<"ID: "<<x.no.id<<" Score: "<<x.score<<endl; // A função só imprime os scores de cada nó

}




}



int main(){


Graph g = leitura_instancia(7); // chama a função para a instância x

Solucao(g);


}





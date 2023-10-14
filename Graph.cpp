#include "Graph.h"

Graph::Graph() {
    // Inicialize membros com valores padrão
    h = 0;
    n = 0;
    numTrips = 0;
    tamTour = 0;
}

// Métodos Get
vector<Node> Graph::getNos(){
    return Nos;
}

list<float> Graph::getTamTrip(){
    return TamTrip;
}

int Graph::getH(){
    return h;
}

int Graph::getN(){
    return n;
}

int Graph::getNumTrips(){
    return numTrips;
}

int Graph::getTamTour(){
    return tamTour;
}

// Métodos Set
void Graph::setH(int h){
    this->h = h;
}

void Graph::setN(int n){
    this->n = n;
}

void Graph::setH0(Node h){
    H0 = h;
}

void Graph::setH1(Node h){
    H1 = h;
}


void Graph::setNumTrips(int numTrips){
    this->numTrips = numTrips;
}

void Graph::setTamTour(int tamTour){
    this->tamTour = tamTour;
}

void Graph::setNos(vector<Node>& nos){
    Nos = nos;
}

void Graph::setTamTrips(float tamTrip){
    TamTrip.push_back(tamTrip);
}

/*float Graph::CalculaDistancia(Node n1, Node n2){
    
    if ((n1.getX() == n2.getX())&&(n1.getY() == n2.getY()))
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
*/

bool Graph::Comparacao(Node f, Node s){
    return (f.getRazao() > s.getRazao());
}

list<Node> Graph::OrdenaCandidatos(Node n){
    cout<<"Criando lista de candidatos"<<endl;
    list<Node> Candidatos;
    cout<<"Copiando os nos para o candidatos"<<endl;
    copy(Nos.begin(), Nos.end(), back_inserter(Candidatos));
    
    cout<<"iterando os candidatos afim da armazenar a razao de cada um deles"<<endl;
    for(auto i:Candidatos){
        if((i.getX() == n.getX() && i.getY() == n.getY()) || i.getVisitado() == 1){
	    cout<<"nao entrou pra solucao"<<endl;
            continue;
	}else{
	    cout<<"entrei para a solucao"<<endl;
            i.setRazao((pow(i.getScore(),2))/i.getDistancia(n.getId()));
	}
    }
    cout<<"sorting"<<endl;
    //Precisa ordenar o vetor, esta dando erro
    Candidatos.sort(Candidatos.begin(),Candidatos.end(), [](Node f, Node s) {return f.getRazao() > s.getRazao();});
    //Candidatos.sort(Candidatos.begin(),Candidatos.end(), Comparacao);
    return Candidatos;

}

void Graph::AddNo(Node no){
    no.setId(Nos.size());       //define uma ID beaseada na quantidade de nos ja existentes no grafo
    for(auto i:Nos){            //calcula a distancia do novo no para cada no
        i.atualizaDistancia(no);
        no.atualizaDistancia(i);
    }
    no.atualizaDistancia(no);   //define a distancia de um no para ele mesmo
    Nos.push_back(no);  //insere o no no grafo
}

void Graph::CalculaSolucao(){
    cout<<"X:"<<Nos[0].getX()<<" Y:"<<Nos[0].getY()<<endl;
    cout<<"Tentando inserir"<<endl;
    list<float>::iterator it = TamTrip.begin();
    for(int i = 0; i<numTrips;i++){
	advance(it,i);
	Inserir(*it);
    }
}

//metodos da busca local


void Graph::Inserir(float trip){
    cout<<"Ordenando Nos"<<endl;
    list<Node> candidatos = OrdenaCandidatos(Nos[0]);
    cout<<"inserindo Nos";
    float sum = 0;
    for(auto i:candidatos){
        if((sum+i.getRazao())<trip){
            sum+=i.getRazao();
            Solucao.push_back(i);
        }
    }
} 


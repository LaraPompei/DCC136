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

list<Node> Graph::OrdenaCandidatos(Node n, bool hotel){
    list<Node> Candidatos;
        Candidatos.clear();
    if(hotel){
        cout<<"Ordenando lista de hoteis"<<endl;
	    copy(Hotel.begin(), Hotel.end(), back_inserter(Candidatos));
	}else{
        cout<<"Ordenando lista de vertices"<<endl;
        for(auto i:Vertices){
            if(!i.getHotel())
                Candidatos.push_back(i);
         }
    	//copy(Vertices.begin(), Vertices.end(), back_inserter(Candidatos));	
	}
    for(auto i:Candidatos){
        if((i.getX() == n.getX() && i.getY() == n.getY()) || i.getVisitado() == 1){
            cout<<"Ignorando o no X="<<i.getX()<<" Y="<<i.getY()<<endl;
            continue;
	    }else{
            cout<<"Calculando a razao do no "<<i.getId()<<endl;
            i.setRazao(i.getScore()/i.getDistancia(n.getId()));
            cout<<"Razao="<<i.getRazao()<<endl<<"Distancia="<<i.getDistancia(n.getId())<<endl;
	    }
    }
    cout<<"Sorting.."<<endl;
    Candidatos.sort([](Node f, Node s) {return f.getRazao() > s.getRazao();});
    for(auto i:Candidatos)
        cout<<"ID:"<<i.getId()<<"; Razao:"<<i.getRazao()<<"; Distancia:"<<i.getDistancia(n.getId())<<"\t";
    cout<<endl;
    cout<<"Candidatos ordenados com sucesso!"<<endl;
    return Candidatos;

}

void Graph::AddNo(Node no){
    no.setId(Nos.size());       //define uma ID beaseada na quantidade de nos ja existentes no grafo
    for(auto i:Nos){            //calcula a distancia do novo no para cada no
        i.atualizaDistancia(no);
        no.atualizaDistancia(i);
    }
    no.atualizaDistancia(no);   //define a distancia de um no para ele mesmo
    Nos.push_back(no);          //insere o no no grafo
	if(no.getHotel()){
		Hotel.push_back(no);
	}else{
		Vertices.push_back(no);
	}
}

void Graph::CalculaSolucao(){
    cout<<"X:"<<H0.getX()<<" Y:"<<H0.getY()<<endl;
    cout<<"Tentando inserir H0 na solucao"<<endl<<endl;
    Solucao.push_back(H0);
    cout<<"Tentando inserir o proximo no"<<endl;
    list<float>::iterator it = TamTrip.begin();
    for(int i = 0; i<numTrips;i++){
		advance(it,i);
        cout<<"Inserindo nos na "<<i<<"o trip de tamanho "<<*it<<endl;
		Inserir(*it);
    }
}

void Graph::ImprimeSolucao(){
	cout<<"Solucao: "<<endl;
	int id = 0;
	for(auto i:Solucao){
		cout<<"X="<<i.getX()<<"\tY:"<<i.getY()<<"\tS:"<<i.getScore()<<"\tdistancia: "<<i.getDistancia(id)<<endl;
		id = i.getId();
	}
}
//metodos da busca local


void Graph::Inserir(float trip){
    cout<<"Ordenando Nos para o primeiro candidato"<<endl;
    list<Node> candidatos = OrdenaCandidatos(Solucao.back(),false); //ordena os melhores candidatos para serem incluidos na nossa nova solucao
    
    cout<<"inserindo Nos na trip"<<endl;
    float sum = 0;
    bool final =0;
	for(auto i:candidatos){
        if((sum+i.getRazao())<trip && !i.getVisitado()){ 
            cout<<"Candidato entra na solucao, Id="<<i.getId()<<endl<<"; Distancia="<<i.getDistancia(Solucao.back().getId())<<endl;
            sum+=i.getDistancia(Solucao.back().getId());
            cout<<"Adicionando candidato na solucao.."<<endl;
            Solucao.push_back(i);
            cout<<"Definindo no como visitado"<<endl;
            i.setVisitado(true);
            cout<<endl<<endl<<"Definindo nova ordem de candidatos.."<<endl;
	    	candidatos = OrdenaCandidatos(i,false);		
        }
    }
    cout<<"Selecionando hotel para concluir a trip"<<endl<<endl;
    candidatos = OrdenaCandidatos(candidatos.back(),true);
    if(sum+candidatos.front().getDistancia(candidatos.front().getDistancia(Solucao.back().getId()))<=trip){
        cout<<"Adicionando hotel na solucao.. ID="<<candidatos.front().getId()<<"; Distancia="<<candidatos.front().getId()<<"; tamTrip="<<sum<<"; tamMaxTrip="<<trip<<endl<<endl;
        Solucao.push_back(candidatos.front());
    }else{
        cout<<"Removendo ultimo ponto turisco acrescentado, pq nao conseguimos chegar ao hotel"<<endl;
        while(sum+candidatos.front().getDistancia(candidatos.front().getDistancia(Solucao.back().getId()))<=trip){
            cout<<"Removendo o elemento ID="<<Solucao.back().getId()<<endl;
            sum -= (Solucao.back()).getDistancia(Solucao[(int(Solucao.size())-2)].getId());
            Solucao.pop_back();
        }
        Solucao.push_back(candidatos.front());
    }
}



#include "Graph.h"

Graph::Graph() {
    // Inicialize membros com valores padrão
    h = 0;
    n = 0;
    numTrips = 0;
    tamTour = 0;
    melhorNo=-1;
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
void Graph::BubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            //cout<<Nos[arr[j]].getRazao()<<'\t';
            if (Nos[arr[j]].getRazao() <  Nos[arr[j + 1]].getRazao()) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        //cout<<endl;

        if (!swapped) {
            break;
        }
    }
    //cout<<endl<<endl;
}

void Graph::AddNo(Node no){
    no.setId(Nos.size());       //define uma ID beaseada na quantidade de nos ja existentes no grafo
    for(auto i:Nos){            //calcula a distancia do novo no para cada no
        i.atualizaDistancia(no);
    }
    no.calculaDistancia(Nos);
    no.atualizaDistancia(no);   //define a distancia de um no para ele mesmo
    Nos.push_back(no);          //insere o no no grafo
	if(no.getHotel()){
		Hotel.push_back(no);
	}else{
		Vertices.push_back(no);
	}
}

vector<int> Graph::SelecionaMelhores(){
    int id =0;
    vector<int> melhores;
    for(auto i:Vertices){
        id = i.getId();
        if(id!=noAtual && !Nos[id].getVisitado()){
            if(dist[id][noAtual]<=distanciaRestante){
                melhores.push_back(id);
                Nos[id].setRazao(Nos[id].getScore()/dist[id][noAtual]);
                //cout<<id<<'\t'<<dist[id][noAtual]<<endl;
            }
        }
    }
    //cout<<endl;
    BubbleSort(melhores);
    /*for(auto i:melhores){
       cout<<Nos[i].getRazao()<<'\t'<<dist[i][noAtual]<<'\t';
    }
    cout<<endl;*/
    return melhores;
}

int Graph::SelecionaHotel(){
    int id = 0;
    int best = H0.getId();
    for(auto i:Hotel){
        id = i.getId();
        if(dist[id][noAtual]<dist[id][best]){
           best = id; 
        }
    }
    return best;
}

void Graph::Solve(){
    noAtual = H0.getId();
    int aux,hotel =0;
    score = 0;
    //cout<<"No inicial "<<noAtual<<endl;
    for(auto i:TamTrip){
        distanciaRestante = i;
        cout<<"Distancia restante: "<<distanciaRestante<<"\t"<<endl;
        vector<int> candidatos = SelecionaMelhores();
        for(auto c:candidatos){
            if(distanciaRestante-dist[noAtual][c]>0){
                //cout<<dist[noAtual][c]<<'\t';
                distanciaRestante = distanciaRestante-dist[noAtual][c];
                //cout<<dist[noAtual][c]<<'\t'<<endl;
                Nos[c].setVisitado(true);
                solution.push_back(c);
                noAtual = c;
                score+=Nos[c].getScore();
                cout<<dist[noAtual][c]<<"\t"<<distanciaRestante<<endl;
            }
        }
        if(i == TamTrip.back())
            hotel = H1.getId();
        else
            hotel = SelecionaHotel();
        cout<<dist[noAtual][hotel]<<endl;
        if(distanciaRestante-dist[noAtual][hotel]>=0){
           cout<<"Hotel"<<endl;
           noAtual = hotel;
        }else{
            cout<<"Nao cabe"<<endl;
            while(distanciaRestante<dist[noAtual][hotel]){
                cout<<"entrei no while"<<endl;
                aux = noAtual;
                solution.pop_back();
                noAtual = solution.back();
                cerr<<"distanciaRestante:"<<distanciaRestante<<'\t';
                distanciaRestante += dist[noAtual][aux];
                cerr<<"distanciaRestante:"<<distanciaRestante<<endl;
            }
        }
        distanciaRestante-=dist[noAtual][hotel];
        //cout<<distanciaRestante<<endl;
        solution.push_back(hotel);
   }

   for(auto i:solution)
       cout<<i<<'\t'<<"X:"<<Nos[i].getX()<<"\tY:"<<Nos[i].getY()<<"\tScore:"<<Nos[i].getScore()<<endl;
   cout<<endl;
   cout<<"Score = "<<score<<endl; 
}

void Graph::CalculaDistancias(){
    dist = new float*[Nos.size()];
    for(int i =0; i<Nos.size();i++){
        dist[i] = new float[Nos.size()];
    }
    for(auto i:Nos){
        for(auto j:Nos){
            dist[i.getId()][j.getId()] = sqrt(pow((i.getX()-j.getX()),2)+pow((i.getY()-j.getY()),2));
            if(dist[i.getId()][j.getId()] <0){
                //cout<<"Xi: "<<i.getX()<<"\tYi: "<<i.getY()<<endl<<"Xj: "<<j.getX()<<"\tYj: "<< j.getY()<<endl;
                //cout<<dist[i.getId()][j.getId()]<<endl<<endl;
            }
        }
    }
}

/*void Graph::MoveMelhor(){
    float d = 0;
    int aux,p;
    for(auto i:solution){
        if(i!=solution.front()&&i!=solution.back()){
            d=dist[i][i-1]+dist[i][i+1]
            for(auto j:solution){
                if(dis[i][j]+dist[i][j+1]<d){
                    aux = solution[i];
                    p = find(solution.begin(), solution.end(), i);
                    solution.erase(p);
                    p = find(solution.begin(),solution.end(),j);
                    solution.insert(aux,p+1);
                }   
            }
        }else
            continue;
    }
}*/

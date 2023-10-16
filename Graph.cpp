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
/*
void bubbleSort(vector<Node>& arr) {
    int n = arr.size();
    bool swapped;
    Node aux;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;

        for (int j = 0; j < n - 1 - i; j++) {
            cout<<arr[j].getRazao()<<endl;
            if (arr[j].getScore() <  arr[j + 1].getScore()) {
                //swap(arr[j], arr[j + 1]);
                aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;   
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }
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

void Graph::OrdenaCandidatos(Node n, bool hotel){
    Candidatos.clear();
    float d=0.0;
    if(hotel){
        cout<<"Ordenando lista de hoteis"<<endl;
	    Candidatos = Hotel;
        //copy(Hotel.begin(), Hotel.end(), back_inserter(Candidatos));
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
            d = i.getDistancia(n.getId());
            if(d>0){
                i.setRazao(i.getScore()/i.getDistancia(n.getId()));
                cout<<"Razao="<<i.getRazao()<<endl<<"Distancia="<<i.getDistancia(n.getId())<<endl;
            }else{
                cout<<"Erro entre os nos "<<i.getId()<<" e "<<n.getId()<<endl;
           }
	    }
    }
    cout<<"Sorting.."<<endl;
    //bubbleSort(Candidatos);
    //Candidatos.sort([](Node f, Node s) {return f.getRazao() > s.getRazao();});
    for(auto i:Candidatos)
        cout<<"ID:"<<i.getId()<<"; Razao:"<<i.getRazao()<<"; Distancia:"<<i.getDistancia(n.getId())<<"\t";
    cout<<endl;
    cout<<"Candidatos ordenados com sucesso!"<<endl;
    //return Candidatos;

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

bool Graph::Comparacao(Node f, Node s){
    return f.getRazao()<s.getRazao();
}

void Graph::ImprimeSolucao(){
	cout<<"Solucao: "<<endl;
	int id = Solucao.front().getId();
    cout<<"Id="<<id<<endl;
	for(auto i:Solucao){
		cout<<"X="<<i.getX();
        cout<<"\tY:"<<i.getY();
        cout<<"\tS:"<<i.getScore();
        if(i.getId()!=id)
            cout<<"\tdistancia: "<<i.getDistancia(id);
		id = i.getId();
        cout<<endl;
	}
}
//metodos da busca local


void Graph::Inserir(float trip){
    cout<<"Ordenando Nos para o primeiro candidato"<<endl;
    //vector<Node> Candidatos = OrdenaCandidatos(Solucao.back(),false); //ordena os melhores Candidatos para serem incluidos na nossa nova solucao
    OrdenaCandidatos(Solucao.back(),false);
    cout<<"inserindo Nos na trip"<<endl;
    float sum = 0;
    bool final =0;
	for(auto i:Candidatos){
        if((sum+i.getRazao())<trip && !i.getVisitado()){ 
            cout<<"Candidato entra na solucao, Id="<<i.getId()<<endl<<"; Distancia="<<i.getDistancia(Solucao.back().getId())<<endl;
            sum+=i.getDistancia(Solucao.back().getId());
            cout<<"Adicionando candidato na solucao.."<<endl;
            Solucao.push_back(i);
            cout<<"Definindo no como visitado"<<endl;
            i.setVisitado(true);
            cout<<endl<<endl<<"Definindo nova ordem de Candidatos.."<<endl;
	    	//Candidatos = OrdenaCandidatos(i,false);		
            OrdenaCandidatos(i,false);
        }
    }
    cout<<"Selecionando hotel para concluir a trip"<<endl<<endl;
    //Candidatos = OrdenaCandidatos(Candidatos.back(),true);
    OrdenaCandidatos(Candidatos.back(),true);
    if(sum+Candidatos.front().getDistancia(Candidatos.front().getDistancia(Solucao.back().getId()))<=trip){
        cout<<"Adicionando hotel na solucao.. ID="<<Candidatos.front().getId()<<"; Distancia="<<Candidatos.front().getId()<<"; tamTrip="<<sum<<"; tamMaxTrip="<<trip<<endl<<endl;
        Solucao.push_back(Candidatos.front());
    }else{
        cout<<"Removendo ultimo ponto turisco acrescentado, pq nao conseguimos chegar ao hotel"<<endl;
        while(sum+Candidatos.front().getDistancia(Candidatos.front().getDistancia(Solucao.back().getId()))<=trip){
            cout<<"Removendo o elemento ID="<<Solucao.back().getId()<<endl;
            sum -= (Solucao.back()).getDistancia(Solucao[(int(Solucao.size())-2)].getId());
            Solucao.pop_back();
        }
        Solucao.push_back(Candidatos.front());
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
                //cout<<id<<'\t';
            }
        }
    }
    //cout<<endl;
    BubbleSort(melhores);
    for(auto i:melhores){
       cout<<Nos[i].getRazao()<<'\t';
    }
    cout<<endl;
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
    cout<<"No inicial "<<noAtual<<endl;
    for(auto i:TamTrip){
        distanciaRestante = i;
        cout<<"Distancia restante: "<<distanciaRestante<<"\t"<<endl;
        vector<int> candidatos = SelecionaMelhores();
        for(auto c:candidatos){
            if(distanciaRestante-dist[noAtual][c]>0){
                Nos[c].setVisitado(true);
                solution.push_back(c);
                noAtual = c;
                score+=Nos[c].getScore();
                distanciaRestante-=dist[noAtual][c];
            }
        }
        if(i == TamTrip.back())
            hotel = H1.getId();
        else
            hotel = SelecionaHotel();
        if(distanciaRestante-dist[noAtual][hotel]>=0){
           noAtual = hotel;
        }else{
            while(distanciaRestante-dist[noAtual][hotel]>=0){
                aux = noAtual;
                solution.pop_back();
                noAtual = solution.back();
                distanciaRestante += dist[noAtual][aux];
            }
        }
        distanciaRestante-=dist[noAtual][hotel];
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
                cout<<"Xi: "<<i.getX()<<"\tYi: "<<i.getY()<<endl<<"Xj: "<<j.getX()<<"\tYj: "<< j.getY()<<endl;
                cout<<dist[i.getId()][j.getId()]<<endl<<endl;
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

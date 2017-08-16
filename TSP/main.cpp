#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

#include "Tour.h"
#include "Utils.h"
#include "Map.h"

using std::cin;
using std::vector;

const int CTRL{50};

bool end(vector<Tour>&);
bool interv(double&,double&);
void mutate(vector<Tour>&);
void crossPop(vector<Tour>&);

int main(){
    srand((unsigned)time(0));
    int tam_pop,tam_map;

    vector<Tour> pop;

    cout<<"Digite o tamanho da populacao e a quantidade de cidades: ";
    cin >> tam_pop >> tam_map;

    //cria o mapa
    Map objMap(tam_map);

    //gera a primeira população 
    for(int i=0; i<tam_pop; i++){
        Tour objT(objMap);
        pop.push_back(objT);
    }

    while(end(pop)){
        //seleciona a proxima pop
        cout<<"fazendo torneio"<<endl;
        pop=tournament(pop);
        cout<<"passou do torneio"<<endl;
        //realiza o crossover
        cout<<"fazendo cross"<<endl;
        crossPop(pop);
        cout<<"saiu do cross"<<endl;
        //realiza a mutação
        cout<<"fazendo mutação"<<endl;
        mutate(pop);
        cout<<"passou do mutate"<<endl;
    }

    cout<<getMinFit(pop);

    return(0);
}

bool end(vector<Tour> &t){
    //conta quantas gerações se passaram sem que ocorra uma diferença de 5% na fitness máxima e mínima
    static int cont{0};

    double max{getMaxFit(t)},min{getMinFit(t)};

    if(interv(min,max)){
        cont++;
    }else{
        cont=0;
    }
    if(cont >= CTRL){
        return(false);
    }else{
        return(true);
    }
}

bool interv(double &min, double &max){
    if((max-min)<(max*0.05)){
        return(true);
    }else{
        return(false);
    }
}

void mutate(vector<Tour> &t){
    for(Tour objT : t){
        mutation(objT);
    }
}

void crossPop(vector<Tour> &t){
    for(int i=0;i<t.size()/2;i++){
        crossover(t[rand()%t.size()],t[rand()%t.size()]);
    }
}


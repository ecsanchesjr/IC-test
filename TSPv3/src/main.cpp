#include <iostream>
#include <cstdlib>
#include <ctime>

#include "City.h"
#include "Map.h"
#include "Tour.h"
#include "Population.h"

using std::cout;
using std::endl;
using std::cin;

const int LIMIT{50000};

bool end(Population&);

int main(){
    int i{0},mapSize{0},popSize{0};
    srand(time(NULL));

    cout<<"----------------------------TSP v3----------------------------"<<endl;
    cout<<"Digite o numero de cidades do mapa: ";
    cin>>mapSize;
    cout<<"Digite o tamanho de sua populacao: ";
    cin>>popSize;
    cout<<"comecando o algoritmo..."<<endl;
    

    Map map(mapSize);

    Population *pop = new Population(map,popSize);

    while(!end(*pop)){   // Roda enquanto nenhuma das condições de parada forem atendidas

        Population *oldPop = pop;
        pop = (*pop).newGeneration();
        delete oldPop;
        ++i;
    }

    cout<<(*pop)<<endl;
    cout<<i<<" geracoes depois!"<<endl;

    return(0);
}

bool end(Population &pop){
    static int genWithoutChanges{0};
    static double maxFitEver{0.0};
    double maxFit{maxFitness(pop.getPopulation())},minFit{minFitness(pop.getPopulation())};
    if(maxFit>maxFitEver){
        maxFitEver = maxFit;
        genWithoutChanges = 0;
    }else{
        genWithoutChanges++;
    }
    if((maxFit-minFit)<(maxFit*0.05)){   // Amplitude de 5% entre a maior e menor fitness
        cout<<"Populacao convergiu!"<<endl;
        cout<<"Fitness maxima: "<<maxFit<<endl;
        return(true);
    }else if(genWithoutChanges >= LIMIT){  // Gerações sem alteração da melhor fitness
        cout<<"Populacao sem melhora a "<<genWithoutChanges<<" geracoes!"<<endl;
        cout<<"Fitness maxima: "<<maxFit<<endl;
        return(true);
    }else{
        return(false);
    }
}
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include "City.h"
#include "Map.h"
#include "Tour.h"
#include "Population.h"
#include "ImportData.h"

using std::cout;
using std::endl;
using std::cin;

typedef std::chrono::high_resolution_clock Clock;

const long int LIM_UNCHANGED{5000};
const long int LIMIT_ALL{50000};


bool end(Population&);

int main(){
    long int i{0},mapSize{0},popSize{0};
    string nome{""};
    srand(time(NULL));

    cout<<"----------------------------TSP v4----------------------------"<<endl;
    cout<<"Digite o nome do arquivo .tsp: ";
    cin>>nome;
    cout<<"Digite o tamanho de sua populacao: ";
    cin>>popSize;
    
    auto tInicial=Clock::now();  //startando cronometro

    cout<<"Comecando o algoritmo ..."<<endl;
    ImportData dataFile(nome);
    dataFile.printInfos();

    Map map(dataFile.getCitiesCoord());

    for(City c : map.getCityList()){
        cout<<c<<endl;
    }

    cout<<"comecando a processar..."<<endl;

    Population *pop = new Population(map,popSize);

    cout<<"Primeira populacao: "<<endl;
    cout<<(*pop)<<endl;
    cout<<"Melhor fitness: "<<maxFitness((*pop).getPopulation())<<endl;
    cout<<"distancia: "<<(1/maxFitness((*pop).getPopulation())*10000)<<endl;
    

    while(!end(*pop)){   // Roda enquanto nenhuma das condições de parada forem atendidas

        Population *oldPop = pop;
        pop = (*pop).newGeneration();
        delete oldPop;
        ++i;
    }

    auto tFinal=Clock::now();

    cout<<(*pop)<<endl;
    cout<<i<<" geracoes depois!"<<endl;
    cout<<"Fitness maxima: "<<maxFitness((*pop).getPopulation())<<endl;
    cout<<"distancia: "<<(1/maxFitness((*pop).getPopulation())*10000)<<endl;

    cout<<"-----------------------------" << endl;

    cout<<"Tempo de execucao: "<<std::chrono::duration_cast<std::chrono::seconds>(tFinal - tInicial).count()<<" segundos!"<<endl;
    cout << endl;
    dataFile.printInfos();
    return(0);
}

/* bool end(Population &pop){
    static long int genWithoutChanges{0};
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
        return(true);
    }else if(genWithoutChanges >= LIMIT){  // Gerações sem alteração da melhor fitness
        cout<<"Populacao sem melhora a "<<genWithoutChanges<<" geracoes!"<<endl;
        return(true);
    }else{
        return(false);
    }
} */

bool end(Population &pop){
    static long int genWithoutChanges{0};
    static double maxFitEver{0.0};
    double maxFit{maxFitness(pop.getPopulation())}, minFit{minFitness(pop.getPopulation())};

    if(maxFit > maxFitEver){  // contagem de gerações inalteradas
        maxFitEver = maxFit;
        genWithoutChanges = 0;
        pop.resetMutMult(); // ocorreu alteração, multiplicador volta para o valor padrão
    }else{
        genWithoutChanges++;
    }

    if((maxFit-minFit) < (maxFit*0.05)){
        cout<<"População convergiu!"<<endl;
        return(true);
    }else if(genWithoutChanges >= LIM_UNCHANGED){
        pop.increaseMutMult();  // vai subir o multiplicador de chance de mutação em 1 (mutação padrão de 2% * multiplicador)
        if(genWithoutChanges >= LIMIT_ALL){
            cout<<"Fitness inalterada com "<<genWithoutChanges<<" de gerações!"<<endl;
            return(true);
        }
    }else{
        return(false);
    }
}
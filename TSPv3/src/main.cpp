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

const int LIMIT{500};

bool end(Population&);

int main(){
    int i{0};

    srand(time(NULL));

    Map map;

    Population *pop = new Population(map);

    
    cout<<"TSP v3"<<endl;

    while(!end(*pop)){

        Population *oldPop = pop;
        pop = (*pop).newGeneration();
        delete oldPop;
        ++i;
    }

    cout<<(*pop)<<endl;

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
    if((maxFit-minFit)<(maxFit*0.05)){
        cout<<"Populacao convergiu!"<<endl;
        cout<<"Fitness maxima: "<<maxFit<<endl;
        return(true);
    }else if(genWithoutChanges >= LIMIT){
        cout<<"Populacao sem melhora a "<<genWithoutChanges<<" geracoes!"<<endl;
        cout<<"Fitness maxima: "<<maxFit<<endl;
        return(true);
    }else{
        return(false);
    }
}
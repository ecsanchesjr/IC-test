#include <iostream>

#include "City.h"
#include "Map.h"
#include "Tour.h"
#include "Population.h"

using std::cout;
using std::endl;
using std::cin;

const int LIMIT{50};

bool end(Population&);

int main(){
    int i{0};

    Map map;

    Population *pop = new Population(map);

    Tour t = (*pop).elitism();

    //cout<<t<<endl;

    cout<<compareDouble(1.1943,0.898538)<<endl;
    /* 
    cout<<"TSP v3"<<endl;

    while(!end(*pop)){

        Population *oldPop = pop;
        pop = (*pop).newGeneration();
        delete oldPop;
        cout<<"pop size: "<<(*pop).getPopulation().size()<<endl;
        cout<<"Fitness maxima da geracao "<<i<<": "<<maxFitness((*pop).getPopulation())<<endl;
        ++i;
        cin.get();
    }
 */
    //cout<<(*pop)<<endl;

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
        cout<<"Populacao sem melhora a "<<genWithoutChanges<<"geracoes!"<<endl;
        cout<<"Fitness maxima: "<<maxFit<<endl;
        return(true);
    }else{
        return(false);
    }
}
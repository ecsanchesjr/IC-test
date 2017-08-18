#include "Population.h"

Population::Population(Map &map,const int size){
    for(int i=0;i<size;i++){
        population.push_back(Tour(map));
    }
}

vector<Tour> Population::getPopulation(){
    return(population);   
}

ostream& operator<<(ostream &output,Population &pop){
    int i{0};
    for(Tour t : pop.getPopulation()){
        output<<"Tour "<<setfill('0')<<setw(3)<<i<<endl;
        output<<t<<endl;
        ++i;
    }
    return(output);
}


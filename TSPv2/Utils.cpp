#include "Utils.h"

void printCityList(vector<City> &cityList){
    for(City c : cityList){
        cout<<"x "<<c.getX()<<" y "<<c.getY()<<endl;
    }
}

void printListOfTours(Population &pop){
    int i{0};
    for(Tour t :  (*pop.getListOfTour())){
        cout<<"Tour "<<i<<endl;
        printCityList((*t.getRoute()));
        ++i;
        cout<<t.getFitness()<<endl;
        cout<<"<------------>"<<endl;
    }
}


Population* selectPop(Population &pop){

}

Tour elitism(Population &pop){
    double maxFit{maxFitness(pop)};
    for(Tour t : (*pop.getListOfTour())){
        if(compareDouble(t.getFitness(),maxFit)){
            return(t);
        }
    }
}

Tour roulete(Population &pop){
    double sumFitness{0.0},ctrl{0.0};
    int random{0};
    //acha o fitness total da população
    for(Tour t : (*pop.getListOfTour())){
        sumFitness+=t.getFitness();
    }
    //sorteia um número int e então converte ele para o intervalo de 0 até a fitness total
    random = rand()%RES;
    ctrl = convertRanges(random,sumFitness);
    for(Tour t : (*pop.getListOfTour())){
        ctrl-=t.getFitness();
        if(ctrl<=0){
            return(t);
        }
    }
    return((*pop.getListOfTour())[(*pop.getListOfTour()).size()]);
}

void crossover(Tour &t1,Tour &t2){
    
}

void mutation(Tour &t){
    int size = (*t.getRoute()).size();
    for(int i=0;i<size;i++){
        if(rand()%100<2){
            t.swap(rand()%size,rand()%size);
        }
    }
}

double convertRanges(const int n,const double rand){
    return((rand*n)/RES);
}

double maxFitness(Population &pop){
    double max = -1*numeric_limits<double>::max(),fitness{0.0};
    for(Tour t : (*pop.getListOfTour())){
        fitness = t.getFitness();
        if(max < fitness){
            max = fitness;
        }
    }
    return(max);
}

double minFitness(Population &pop){
    double min = numeric_limits<double>::max(),fitness{0.0};
    for(Tour t : (*pop.getListOfTour())){
        fitness = t.getFitness();
        if(min > fitness){
            min = fitness;
        }
    }
    return(min);
}

double compareDouble(const double a,const double b,const double delta){
    return((a-b)<delta);
}
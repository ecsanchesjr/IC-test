#include "Utils.h"

void printCityList(const vector<City> &cityList){
    int i{0};
    for(City c : cityList){
        cout<<i<<" "<<"x "<<c.getX()<<" y "<<c.getY()<<endl;
        i++;
    }
}

void printListOfTours(Population &pop){
    int i{0};
    for(Tour *t :  (pop.getListOfTour())){
        if(i==2){
            break;
        }
        cout<<"Tour "<<i<<endl;
        printCityList((*t).getRoute());
        ++i;
        cout<<(*t).getFitness()<<endl;
        cout<<"<------------>"<<endl;
        
    }
}


Population* selectPop(Population &pop){

}

Tour elitism(Population &pop){
    double maxFit{maxFitness(pop)};
    for(Tour *t : (pop.getListOfTour())){
        if(compareDouble((*t).getFitness(),maxFit)){
            return(*t);
        }
    }
}

Tour roulete(Population &pop){
    double sumFitness{0.0},ctrl{0.0};
    int random{0};
    //acha o fitness total da população
    for(Tour *t : (pop.getListOfTour())){
        sumFitness+=(*t).getFitness();
    }
    //sorteia um número int e então converte ele para o intervalo de 0 até a fitness total
    random = rand()%RES;
    ctrl = convertRanges(random,sumFitness);
    for(Tour *t : (pop.getListOfTour())){
        ctrl-=(*t).getFitness();
        if(ctrl<=0){
            return(*t);
        }
    }
    return(*(pop.getListOfTour())[(pop.getListOfTour()).size()]);
}

void crossover(Population &pop,const int a,const int b){
    vector<Tour*> oldPop = pop.getListOfTour();
    vector<City> tmp1,tmp2;
    int size ={(int)(pop.getListOfTour()).size()},sizeTour{(int)(pop.getListOfTour())[0].getRoute().size()};
    if(rand()%10<10){
        cout<<"entrou"<<endl;

        //copia a ultima metade do cromossomo
        
            for(int j=sizeTour/2;j<sizeTour;j++){
                cout<<"-----------------------"<<endl;
                (*(pop.getListOfTour())[a]).getRoute()[j].printCity();
                (*(pop.getListOfTour())[a]).getRoute()[j] = (*oldPop[b]).getRoute().at(j);
                (*(pop.getListOfTour())[a]).getRoute()[j].printCity();
                oldPop[b].getRoute()[j].printCity();
                cout<<"-----------------------"<<endl;
                
                
                tmp1.push_back(oldPop[b].getRoute()[j]);
                (*pop.getListOfTour())[b].getRoute()[j] = oldPop[a].getRoute()[j];
                tmp2.push_back(oldPop[a].getRoute()[j]);
            }

            //preenche o resto do cromossomo
            for(int i=0;i<oldPop[a].getRoute().size();i++){
                if(contains(tmp1,oldPop[a].getRoute()[i])){
                    //do nothing
                }else{
                    (*pop.getListOfTour())[a].getRoute()[i] = oldPop[a].getRoute()[i];
                }
            }
            for(int i=0;i<oldPop[b].getRoute().size();i++){
                if(contains(tmp1,oldPop[b].getRoute()[i])){
                    //do nothing
                }else{
                    (*pop.getListOfTour())[b].getRoute()[i] = oldPop[b].getRoute()[i];
                }
            }
        

    }
    for(City c : tmp2){
        cout<<"x "<<c.getX()<<" y "<<c.getY()<<endl;
    }
    cout<<"dentro da funcao"<<endl;
    printListOfTours(pop);
    cout<<"dentro da funcao"<<endl;

}

void mutation(Tour &t){
    int size = (t.getRoute()).size();
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

bool contains(vector<City> &vec,City &c){
    for(City objC : vec){
        if(objC == c){
            return(true);
        }
    }
    return(false);
}
#include "Population.h"

Population::Population(Map &map,const int size){
    for(int i=0;i<size;i++){
        population.push_back(Tour(map));
    }
}

Population::Population(){

}

vector<Tour>& Population::getPopulation(){
    return(population);   
}

/*
    realiza a escolha dos tours que irão para a proxima geração
    reserva o melhor tour para ir para a proxima sem alteração
    escolhe os outros por meio da roleta
    faz o crossover nos escolhidos
    faz a mutação 
    e então junta o tour escolhido pelo elitismo e retorna a nova reração
*/
Population* Population::newGeneration(){
    Population  *newPop = new Population;
    Tour best = elitism();
    for(int i=0;i<population.size()-1;i++){
        (*newPop).getPopulation().push_back(roulete());
    }
    newPop->cross();
    newPop->mutate();
    (*newPop).getPopulation().push_back(best);
    return(newPop);
}

void Population::mutate(){
    //faz a mutação em todos os tours
    for(int i=0;i<population.size();i++){
        mutation(i);
    }
}

void Population::cross(){
    //tamanho da população
    int size{(int)population.size()};
    for(int i=0;i<size/2;i++){
        crossover(rand()%size,rand()%size);
    }
}

void Population::mutation(const int a){
    //realiza n mutações, sendo n o tanto de cidades existentes
    int size{(int)population[0].getRoute().size()};
    for(int i=0;i<size;i++){
        if(rand()%100<2){
            population[a].swap(rand()%size,rand()%size);
        }
    }
}

void Population::crossover(const int a,const int b){
    //copia dos tours pais
    Tour tmp1{population[a]},tmp2{population[b]};
    vector<City> order1,order2;
    int size{(int)population[0].getRoute().size()},ctrl1{0},ctrl2{0};
    for(int i=size/2;i<size;i++){
        population[a].getRoute()[i] = tmp2.getRoute()[i];
        order1.push_back(tmp2.getRoute()[i]);
        population[b].getRoute()[i] = tmp1.getRoute()[i];
        order2.push_back(tmp1.getRoute()[i]);
    }
    for(int i=0;i<size;i++){
        if(!contains(order1,tmp1.getRoute()[i])){
            population[a].getRoute()[ctrl1] = tmp1.getRoute()[i];
            ++ctrl1;
        }else{//do nothing
        }
        if(!contains(order2,tmp2.getRoute()[i])){
            population[b].getRoute()[ctrl2] = tmp2.getRoute()[i];
            ++ctrl2;
        }else{//do nothing
        }
    }
}

Tour Population::elitism(){
    double maxFit{maxFitness(population)};
    for(Tour t : (population)){
        if(compareDouble(t.getFitness(),maxFit)){
            return(t);
        }
    }
}

Tour Population::roulete(){
    double sumFitness{0.0},ctrl{0.0};
    int random{0};
    //acha o fitness total da população
    for(Tour t : (population)){
        sumFitness+=(t).getFitness();
    }
    //sorteia um número int e então converte ele para o intervalo de 0 até a fitness total
    random = rand()%RES;
    ctrl = convertRanges(random,sumFitness);
    for(Tour t : (population)){
        ctrl-=(t).getFitness();
        if(ctrl<=0){
            return(t);
        }
    }
    return(population[population.size()-1]);
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


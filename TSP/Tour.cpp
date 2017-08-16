#include "Tour.h"

Tour::Tour(Map& map){
    path = map.getList();
    int index1, index2;
    for(int i=0;i<path.size();i++){
        index1=rand()%path.size();
        index2=rand()%path.size();
        if(index1==index2){
            i--;
        }else{
            swap(path[index1], path[index2]);
        }
    }
}

vector<ObjetoXeY> Tour::getPath(){
    return(path);
}

void Tour::swap(ObjetoXeY &city1, ObjetoXeY &city2){
    ObjetoXeY tmp(city1.x, city1.y);
    city1=city2;
    city2=tmp;
}

double Tour::distance(ObjetoXeY &city1,ObjetoXeY &city2){
    return(sqrt(pow((city1.x - city2.x),2)+pow((city1.y - city2.y),2)));
}

double Tour::getFitness(){
    double soma{0};
    for(int i=0;i<path.size();i++){
        if(i+1 != path.size()){
            soma+=Tour::distance(path[i], path[i+1]);
        }else{
            soma+=Tour::distance(path[i],path[0]);
        }
    }
    return(soma);
}
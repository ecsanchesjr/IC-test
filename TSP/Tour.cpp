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

vector<ObjetoXeY>& Tour::getPath(){
    return(path);
}

void Tour::swap(ObjetoXeY &city1, ObjetoXeY &city2){
    ObjetoXeY tmp(city1.x, city1.y);
    city1=city2;
    city2=tmp;
}
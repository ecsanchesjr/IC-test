#include "Map.h"

Map::Map(const int size){
    int x,y;
    for(int i=0;i<size;i++){
        x = rand()%1000;
        y = rand()%1000;
        ObjetoXeY tmp(x,y);
        list.push_back(tmp);
    }
}

ObjetoXeY Map::getCity(const int i){
    if(i>=list.size()){
    }else{
        return(list[i]);
    }
}

void Map::printList(){
    for(int i=0;i<list.size();i++){
        cout<<list[i].x<<" "<<list[i].y<<endl;
    }
}

vector<ObjetoXeY> Map::getList(){
    return(list);
}


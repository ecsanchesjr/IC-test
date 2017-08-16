#include "Utils.h"

void mutation(Tour& t){
    if(rand()%100 > 2){
        int index1{rand()%t.getPath().size()}, index2{rand()%t.getPath().size()};
        
        while(index1==index2){
            index2=rand()%t.getPath().size();
        }
        t.swap(t.getPath()[index1],t.getPath()[index2]);
    }
}

void crossover(Tour& t1, Tour& t2){
    if(rand()%100 > 80){
        Tour tmp1{t1}, tmp2{t2};
        vector<ObjetoXeY> aux1, aux2;
        
        for(int i=(t1.getPath().size()/2);i<t1.getPath().size();i++){
            aux1[i] = t1.getPath()[i] = tmp2.getPath()[i];
            aux2[i] = t2.getPath()[i] = tmp1.getPath()[i];
        }
        
        for(int i=0; i<t1.getPath().size();i++){
            if(!contains(aux1,tmp1.getPath()[i])){
                t1.getPath()[i] = tmp1.getPath()[i];
            }
            if(!contains(aux2,tmp2.getPath()[i])){
                t2.getPath()[i] = tmp2.getPath()[i];
            }
        }
    }
}

bool contains(vector<ObjetoXeY> &p, ObjetoXeY &c){
    for(int i=0;i<p.size();i++){
        if(p[i].x == c.x && p[i].y == c.y){
            return(true);
        }
    }
    return(false);
}
#include "Utils.h"

void mutation(Tour& t){
    if(rand()%100 < 2){
        cout<<"entrou na mutacao"<<endl;
        int index1{rand()%(int)t.getPath().size()}, index2{rand()%(int)t.getPath().size()};
        
        cout<<"comparando index"<<endl;
        while(index1==index2){
            index2=rand()%t.getPath().size();
        }
        cout<<"terminou comp"<<endl;
        cout<<"chegou no swap";
        t.swap(t.getPath()[index1],t.getPath()[index2]);
        cout<<"fim swap"<<endl;
    }else{
        cout<<"nao mutou"<<endl;
    }

}

void crossover(Tour& t1, Tour& t2){
    if(rand()%100 < 80){
        Tour tmp1(t1.getPath()), tmp2(t2.getPath());
        vector<ObjetoXeY> aux1, aux2;

        cout<<"bug1"<<endl;
        for(int i=(t1.getPath().size()/2);i<t1.getPath().size();i++){
            cout<<"wow1 "<<i<<endl;
            cout<<"t1 "<<t1.getPath().size()<<" t2 "<<t2.getPath().size()<<endl;
            cout<<"tmp1 "<<tmp1.getPath().size()<<" tmp2 "<<tmp2.getPath().size()<<endl;
            t1.getPath()[i] = tmp2.getPath()[i];
            cout<<"wow2"<<endl;
            aux1.push_back(tmp2.getPath()[i]);
            cout<<"wow3"<<endl;
            t2.getPath()[i] = tmp1.getPath()[i];
            cout<<"wow4"<<endl;
            aux2.push_back(tmp1.getPath()[i]);
        }
        cout<<"bug2"<<endl;
        
        for(int i=0; i<t1.getPath().size();i++){
            if(!contains(aux1,tmp1.getPath()[i])){
                t1.getPath()[i] = tmp1.getPath()[i];
            }
            if(!contains(aux2,tmp2.getPath()[i])){
                t2.getPath()[i] = tmp2.getPath()[i];
            }
        }
        cout<<"bug3"<<endl;
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

double getMaxFit(vector<Tour> &t){
    double max = MIN_LIM,tmp{0.0};
    for(Tour objT : t){
        tmp =getFitness(objT.getPath()); 
        if(tmp > max){
            max = tmp;
        }
    }
    return(max);
}

double getMinFit(vector<Tour> &t){
    double min = MAX_LIM,tmp{0.0};
    for(Tour objT : t){
        tmp = getFitness(objT.getPath());
        if(tmp<min){
            min = tmp;
        }
    }
    return(min);
}

double distance(ObjetoXeY &city1,ObjetoXeY &city2){
    return(sqrt(pow((city1.x - city2.x),2)+pow((city1.y - city2.y),2)));
}

double getFitness(vector<ObjetoXeY> &path){
    double soma{0};
    for(int i=0;i<path.size();i++){
        if(i+1 != path.size()){
            soma+=distance(path[i], path[i+1]);
        }else{
            soma+=distance(path[i],path[0]);
        }
    }
    return(soma);
}

vector<Tour> tournament(vector<Tour> &pop){
    vector<Tour> tmp;

    for(int i=0; i<pop.size(); i++){
        tmp.push_back(findMin(pop[rand()%pop.size()], pop[rand()%pop.size()], pop[rand()%pop.size()]));
    }
    return(tmp);
}

Tour findMin(Tour &t1, Tour &t2, Tour &t3){
    if(getFitness(t1.getPath()) > getFitness(t2.getPath()) && getFitness(t3.getPath()) > getFitness(t2.getPath()))
        return(t2);
    if(getFitness(t2.getPath()) > getFitness(t1.getPath()) && getFitness(t3.getPath()) > getFitness(t1.getPath()))
        return(t1);
    if(getFitness(t1.getPath()) > getFitness(t3.getPath()) && getFitness(t2.getPath()) > getFitness(t3.getPath()))
        return(t3);
}
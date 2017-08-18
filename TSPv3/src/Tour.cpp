#include "Tour.h"

Tour::Tour(Map &map){
    int size = map.getCityList().size();
    for(City c : map.getCityList()){
        (route).push_back(c);
    }
    for(int i = 0;i<size;i++){
        swap(rand()%size,rand()%size);
    }
}

vector<City>& Tour::getRoute(){
    return(route);
}

double Tour::getFitness(){
    double sum{0.0};
    for(int i=0;i<(route).size();i++){
        if((i+1) == (route).size()){
            sum+=distance(i,0);
        }else{
            sum+=distance(i,i+1);
        }
    }
    dist = sum;
    return((1/sum)*10000);
}

void Tour::swap(const int a,const int b){
    City tmp = (route)[a];
    (route)[a] = (route)[b];
    (route)[b] = tmp;
}

double Tour::distance(const int a,const int b){
    return(sqrt(pow(((route)[a].getX())-((route)[b].getX()),2)+pow(((route)[a].getY())-((route)[b].getY()),2)));
}

ostream& operator<<(ostream &output,Tour &t){
    int i{0};
    for(City c : t.getRoute()){
        output<<setfill('0')<<setw(2)<<i<<": "<<c<<endl;
        ++i;
    }
    output<<"Fitness: "<<t.getFitness()<<endl;
    output<<"Distance: "<<t.dist<<endl;
    return(output);
}
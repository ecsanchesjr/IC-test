#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <limits>

#include "Tour.h"
#include "Utils.h"
#include "Map.h"

using std::cin;
using std::vector;

const int CTRL{50};

bool end(vector<Tour>&);

bool interv(double&,double&);

int main(){
    srand((unsigned)time(0));
    int tam_pop,tam_map;

    vector<Tour> pop;
    cin >> tam_pop >> tam_map;

    Map objMap(tam_map);

    for(int i=0; i<tam_pop; i++){
        Tour objT(objMap);
        pop.push_back(objT);
    }

    while(){

    }

    return(0);
}

bool end(vector<Tour> t){
    //conta quantas gerações se passaram sem que ocorra uma diferença de 5% na fitness máxima e mínima
    static int cont{0};

    double max{getMaxFit(t)},min{getMinFit(t)};

    if(interv(min,max)){
        cont++;
    }else{
        cont=0;
    }
    if(cont >= CTRL){
        return(false);
    }else{
        return(true);
    }
}

bool interv(double &min, double &max){
    if((max-min)<(max*0.05)){
        return(true);
    }else{
        return(false);
    }
}


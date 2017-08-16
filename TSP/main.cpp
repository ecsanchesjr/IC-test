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

bool end(vector<Tour>&);

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

bool end(vector<Tour> p){

}

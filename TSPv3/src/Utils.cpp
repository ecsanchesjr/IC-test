#include "Utils.h"

#include <iomanip>
using namespace std;

double convertRanges(const int n,const double rand){
    return((rand*n)/RES);
}

double compareDouble(const double a,const double b,const double delta){
    double relativeDelta{((a>b)?a:b)*delta};
    return(abs(a-b)<relativeDelta);
}

double maxFitness(vector<Tour> &tours){
    double max = -1*numeric_limits<double>::max(),fitness{0.0};
    for(Tour t : tours){
        fitness = t.getFitness();
        if(max < fitness){
            max = fitness;
        }
    }
    return(max);
}

double minFitness(vector<Tour> &tours){
    double min = numeric_limits<double>::max(),fitness{0.0};
    for(Tour t : tours){
        fitness = t.getFitness();
        if(min > fitness){
            min = fitness;
        }
    }
    return(min);
}

bool contains(vector<City> &vec,City &c){
    for(City objC : vec){
        if(objC == c){
            return(true);
        }
    }
    return(false);
}
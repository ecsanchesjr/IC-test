#ifndef TOUR_H
#define TOUR_H

#include <vector>
#include <cmath>
#include "City.h"
#include "Map.h"

using std::vector;

class Tour{

public:
    Tour(Map&);
    vector<City>* getRoute();
    double getFitness();
    void swap(const int,const int);
private:
    vector<City> *route;
    double distance(const int,const int);
};

#endif
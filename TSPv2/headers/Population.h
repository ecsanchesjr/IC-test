#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "Tour.h"

using std::vector;

class Population{

public:
    Population(Map&,const int = 10);
    vector<Tour*> getListOfTour();
private:
    vector<Tour*> listOfTour;
};

#endif
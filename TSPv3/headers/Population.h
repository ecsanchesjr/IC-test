#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "Tour.h"
#include "Map.h"

using std::vector;
using std::ostream;
using std::setfill;
using std::setw;

class Population{

    friend ostream& operator<<(ostream&,Population &);

public:
    Population(Map&,const int=10);
    vector<Tour> getPopulation();
private:
    vector<Tour> population;
};
#endif
#ifndef TOUR_H
#define TOUR_H

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "City.h"
#include "Map.h"

using std::vector;
using std::ostream;
using std::setfill;
using std::setw;

class Tour{

    friend ostream& operator<<(ostream&,Tour &);

public:
    Tour(Map&);
    vector<City>& getRoute();
    double getFitness();
    void swap(const int,const int);
private:
    vector<City> route;
    double dist{0};
    double distance(const int,const int);
};

#endif
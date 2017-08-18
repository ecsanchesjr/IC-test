#ifndef UTILS_H
#define UTILS_H

#include <limits>
#include "City.h"
#include "Population.h"

//foward declaration
class Population;

using std::numeric_limits;

const int RES = 10000;

double convertRanges(const int,const double);

double maxFitness(vector<Tour>&);

double minFitness(vector<Tour>&);

double compareDouble(const double,const double,const double = 0.000001);

bool contains(vector<City>&,City&);

#endif
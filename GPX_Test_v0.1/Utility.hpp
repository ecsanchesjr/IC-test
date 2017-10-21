#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <map>
#include "City.hpp"
#include "Tour.hpp"
#include "CityNode.hpp"

using std::map;

double distance(City&, City&);

map<int, CityNode*> mapTour(Tour&); 

void DELETE_MAP_POINTERS();

#endif
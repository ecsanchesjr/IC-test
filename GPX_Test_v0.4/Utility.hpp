#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <iterator>
#include <map>
#include <string>

#include "City.hpp"
#include "CityNode.hpp"
#include "Tour.hpp"

using std::string;
using std::to_string;
using std::map;
using std::iterator;
using std::make_pair;

// double distance(City&, City&);

double distance(double, double, double, double);

map<string, CityNode*> mapTour(Tour&);

void DELETE_MAP_POINTERS();

void printMap(map<string, CityNode*>&);

#endif
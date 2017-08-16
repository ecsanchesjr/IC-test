#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <limits>

#include <iostream>
using namespace std;

#include "Tour.h"
#include "ObjetoXeY.h"

const double MAX_LIM{std::numeric_limits<double>::max()};
const double MIN_LIM{std::numeric_limits<double>::min()};

void crossover(Tour&, Tour&);

void mutation(Tour&);

bool contains(vector<ObjetoXeY>&,ObjetoXeY&);

double getMaxFit(vector<Tour>&);

double getMinFit(vector<Tour>&);

double distance(ObjetoXeY&,ObjetoXeY&);

double getFitness(vector<ObjetoXeY>&);

vector<Tour> tournament(vector<Tour>&);

Tour findMin(Tour&, Tour&, Tour&);

#endif
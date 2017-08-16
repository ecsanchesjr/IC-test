#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "Tour.h"
#include "ObjetoXeY.h"

void crossover(Tour&, Tour&);

void mutation(Tour&);

bool contains(vector<ObjetoXeY>&,ObjetoXeY&);

double getMaxFit(vector<ObjetoXeY>&);

double getMinFit(vector<ObjetoXeY>&);

#endif
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <limits>
#include <cstdlib>
#include "City.h"
#include "Population.h"
#include "Tour.h"

using std::cout;
using std::endl;
using std::vector;
using std::numeric_limits;

const int RES = 10000;

/*
    funções de impresão
*/
void printCityList(vector<City>&);

void printListOfTours(Population&);


/*
    funções do algoritmo genético
*/
/*
    seleciona o melhor cromossomo para passar para a proxima população sem alteração
    preenche o resto da população por meio da roleta e então aplica o crossover e a mutação neles
*/
Population* selectPop(Population&);

Tour elitism(Population&);

Tour roulete(Population&);

void crossover(Tour&,Tour&);

void mutation(Tour&);

/*
    funções de suporte para o alg genético
*/
double convertRanges(const int,const double);

double maxFitness(Population&);

double minFitness(Population&);

double compareDouble(const double,const double,const double=0.00001);


#endif
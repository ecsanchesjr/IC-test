#ifndef TOUR_H
#define TOUR_H

#include <vector>
#include <cmath>
#include "Map.h"
#include "ObjetoXeY.h"

using std::vector;

class Tour{

public:
    Tour(Map&);
    void swap(ObjetoXeY&,ObjetoXeY&);
    double getFitness();
    vector<ObjetoXeY> getPath();
private:
    vector<ObjetoXeY> path;
    double distance(ObjetoXeY&,ObjetoXeY&);
    
};

#endif
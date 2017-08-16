#ifndef MAP_H
#define MAP_H

#include <vector>
#include <cstdlib>
#include <iostream>
#include "ObjetoXeY.h"

using std::vector;
using std::cout;
using std::endl;

class Map{

public:
    Map(const int);
    ObjetoXeY getCity(const int);
    void printList();
    vector<ObjetoXeY> getList();
private:
    vector<ObjetoXeY> list;
};

#endif
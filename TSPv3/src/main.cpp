#include <iostream>

#include "City.h"
#include "Map.h"
#include "Tour.h"
#include "Population.h"

using std::cout;
using std::endl;

int main(){

    Map map;

    Population pop(map);

    cout<<pop<<endl;

    return(0);
}
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Map.h"
#include "Tour.h"
#include "Utils.h"

using std::cout;
using std::endl;

int main(){
    srand(time(NULL));

    Map m1;

    Population p1(m1);

    printListOfTours(p1);

    crossover(p1,0,1);

    printListOfTours(p1);
    

    return(0);
}
#include <iostream>
#include "Map.h"
#include "Tour.h"
#include "Utils.h"


using std::cout;
using std::endl;

int main(){


    Map test;

    Population pop(test,10);

    printListOfTours(pop);

    return(0);
}
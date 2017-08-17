#include <iostream>
#include "Map.h"
#include "Tour.h"
#include "Utils.h"

using std::cout;
using std::endl;

int main(){

    Map m1;

    Tour t(m1);

    printCityList(*t.getRoute());

    return(0);
}
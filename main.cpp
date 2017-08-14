#include <iostream>
#include "Chromosome.h"
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main(){

    Chromosome<char> c;
    vector<char> dataC = {'1','0','1','0','0'};

    c.setData(dataC);

    c.printData();

    Chromosome<int> cI;
    vector<int> dataI = {1,2,3,1,4,1,2};
    
    cI.setData(dataI);
    cI.printData();

    return(0);
}
#include "Utils.h"

void printCityList(vector<City> &cityList){
    for(City c : cityList){
        cout<<"x "<<c.getX()<<" y "<<c.getY()<<endl;
    }
}

void printListOfTours(Population &pop){
    int i{0};
    for(Tour t :  (*pop.getListOfTour())){
        cout<<"Tour "<<i<<endl;
        printCityList((*t.getRoute()));
        ++i;
        cout<<"<------------>"<<endl;
    }
}
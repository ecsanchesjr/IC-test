#include "Population.h"

Population::Population(Map &map, const int size){
    listOfTour = new vector<Tour>;
    for(int i=0;i<size;i++){
        (*listOfTour).push_back(Tour(map));
    }
}

vector<Tour>* Population::getListOfTour(){
    return(listOfTour);
}
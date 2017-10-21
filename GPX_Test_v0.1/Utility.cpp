#include "Utility.hpp"

double distance(City& c1, City& c2){
    return( sqrt( pow((c1.getX() - c2.getX()),2) + pow((c1.getX() - c2.getY()), 2) ) );
}

map<int, CityNode*> mapTour(Tour& t){
    
}
#include "Tour.hpp"

Tour::Tour(){}

Tour::Tour(vector<City> tour):tour(tour){}

void Tour::setTour(vector<City> tour){
    this->tour = tour;
}

vector<City>& Tour::getTour(){
    return tour;
}
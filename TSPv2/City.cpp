#include "City.h"

City::City(){
    this->x = 0;
    this->y = 0;
}

City::City(const double x, const double y):x(x),y(y){}

double City::getX() const{return(x);}

double City::getY() const{return(y);}

void City::setX(const double x){this->x = x;}

void City::setY(const double y){this->y = y;}
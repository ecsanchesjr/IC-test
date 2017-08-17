#ifndef CITY_H
#define CITY_H

#include <iostream>
using namespace std;

class City{

public:
    City();
    City(const double,const double);
    double getX() const;
    double getY() const;
    void setX(const double);
    void setY(const double);

    //overload do operador de comparação
    bool operator==(const City &) const;
    //fazer overload depois
    void printCity();
private:
    double x;
    double y;
};

#endif
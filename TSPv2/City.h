#ifndef CITY_H
#define CITY_H

class City{

public:
    City();
    City(const double,const double);
    double getX() const;
    double getY() const;
    void setX(const double);
    void setY(const double);
private:
    double x;
    double y;
};

#endif
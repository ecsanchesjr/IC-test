#ifndef TOUR_HPP
#define TOUR_HPP

#include <vector>
#include "City.hpp"

using std::vector;

class Tour{
public:
    Tour(vector<City>);

    void setTour(vector<City>);

    vector<City>& getTour();
private:
    vector<City> tour;
};

#endif
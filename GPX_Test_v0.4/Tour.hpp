#ifndef TOUR_HPP
#define TOUR_HPP

#include "City.hpp"
#include <vector>

using std::vector;

class Tour {
public:
    Tour();
    Tour(vector<City>);

    void setTour(vector<City>);

    vector<City>& getTour();

private:
    vector<City> tour;
};

#endif
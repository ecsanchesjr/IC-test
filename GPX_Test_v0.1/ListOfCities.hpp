#ifndef LISTOFCITIES_H
#define LISTOFCITIES_H

#include <vector>
#include "City.hpp"

using std::vector;

class ListOfCities{
public:
    vector<City>& getCitiesList();

private:
    vector<City> citiesList;
};

#endif
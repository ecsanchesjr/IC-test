#include "City.hpp"
#include "GPX2.hpp"
#include "ListOfCities.hpp"
#include "Tour.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// Tours já criados no arquivo "Tours.TSP"

int main()
{
    vector<City> cities, cities2;

    cities.push_back(City(1, 0.0, 0.0));
    cities.push_back(City(2, 0.0, -1.0));
    cities.push_back(City(4, 1.0, -1.0)); 
    cities.push_back(City(6, 2.0, 1.0));
    cities.push_back(City(7, 3.0, 0.0));  
    cities.push_back(City(9, 4.0, 0.0));
    cities.push_back(City(12, 5.0, -1.0));
    cities.push_back(City(11, 5.0, 0.0)); 
    cities.push_back(City(10, 4.0, -1.0)); 
    cities.push_back(City(8, 3.0, -1.0));  
    cities.push_back(City(5, 2.0, 0.0)); 
    cities.push_back(City(3, 1.0, 0.0));

    cities2.push_back(City(1, 0.0, 0.0));
    cities2.push_back(City(4, 1.0, -1.0)); 
    cities2.push_back(City(6, 2.0, 1.0));
    cities2.push_back(City(8, 3.0, -1.0)); 
    cities2.push_back(City(10, 4.0, -1.0));  
    cities2.push_back(City(12, 5.0, -1.0));
    cities2.push_back(City(11, 5.0, 0.0)); 
    cities2.push_back(City(9, 4.0, 0.0));
    cities2.push_back(City(7, 3.0, 0.0));  
    cities2.push_back(City(5, 2.0, 0.0)); 
    cities2.push_back(City(3, 1.0, 0.0));
    cities2.push_back(City(2, 0.0, -1.0));

    Tour t(cities);
    Tour t2(cities2);

    GPX2::crossover(t, t2);
    cout<<"THE END"<<endl;
}
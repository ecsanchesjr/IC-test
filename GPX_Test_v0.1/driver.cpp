#include <iostream>
#include <vector>
#include <iterator>
#include "Utility.hpp"
#include "Tour.hpp"
#include "City.hpp"

using namespace std;

int main(){
    vector<City> cities;

    cities.push_back(City(1, 0.0, 0.0));
    cities.push_back(City(2, 0.0, 1.0));
    cities.push_back(City(3, 1.0, 0.0));
    cities.push_back(City(4, 1.0, 1.0));
    cities.push_back(City(6, 2.0, 1.0));
    cities.push_back(City(5, 2.0, 0.0));

    Tour t(cities);

    map<int, CityNode*> mapVSF = mapTour(t);

    map<int, CityNode*>::iterator it = mapVSF.begin();

    while(it != mapVSF.end()){
        cout << " " << it->first << " | " << it->second->getId() << " " << endl;

        cout << "==========================" << endl;

        for(int i=0; i<2; i++){
            cout << " " << it->second->getEdges().at(i).first->getId() << " | " << it->second->getEdges().at(i).second << endl;
        }
        it++;

        cout << "-----------------------------------------------------------------------------" << endl;
    }
}
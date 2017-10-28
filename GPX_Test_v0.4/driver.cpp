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
    Tour t, t2, offspring;

    cities.push_back(City(1, 0.0, 1.0));
    cities.push_back(City(4, 1.0, 1.0));
    cities.push_back(City(5, 1.0, 2.0));
    cities.push_back(City(2, 0.0, 2.0));
    cities.push_back(City(6, 1.0, 3.0));
    cities.push_back(City(8, 2.0, 3.0)); 
    cities.push_back(City(12, 2.0, 3.0));  
    cities.push_back(City(11, 3.0, 2.0));
    cities.push_back(City(14, 4.0, 2.0));  
    cities.push_back(City(13, 4.0, 1.0)); 
    cities.push_back(City(10, 3.0, 1.0));
    cities.push_back(City(9, 3.0, 0.0));  
    cities.push_back(City(7, 2.0, 0.0)); 
    cities.push_back(City(3, 1.0, 0.0));

    cities2.push_back(City(1, 0.0, 1.0));
    cities2.push_back(City(2, 0.0, 2.0));
    cities2.push_back(City(5, 1.0, 2.0));
    cities2.push_back(City(6, 1.0, 3.0));
    cities2.push_back(City(8, 2.0, 3.0)); 
    cities2.push_back(City(12, 2.0, 3.0));  
    cities2.push_back(City(14, 4.0, 2.0));  
    cities2.push_back(City(11, 3.0, 2.0));
    cities2.push_back(City(10, 3.0, 1.0));
    cities2.push_back(City(13, 4.0, 1.0)); 
    cities2.push_back(City(9, 3.0, 0.0));  
    cities2.push_back(City(7, 2.0, 0.0)); 
    cities2.push_back(City(3, 1.0, 0.0));
    cities2.push_back(City(4, 1.0, 1.0));

    t=cities; t2=cities2;

    cout<<"red ";
    for(City c : t.getTour()){
        cout<<c.getId()<<" ";
    }
    cout<<endl;
    
    cout<<"blue ";
    for(City c : t2.getTour()){
        cout<<c.getId()<<" ";
    }
    cout<<endl;

    offspring = GPX2::crossover(t, t2);

    cout<<"offspring ";
    for(City c : offspring.getTour()){
        cout<<c.getId()<<" ";
    }
    cout<<endl;

    cout<<"dist t "<<t.getFitness()<<"\n";
    cout<<"dist t2 "<<t2.getFitness()<<"\n";
    cout<<"dist offspring "<<offspring.getFitness()<<endl;

    cout<<"THE END"<<endl;
}
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <deque>
#include "Utility.hpp"
#include "Tour.hpp"
#include "City.hpp"
#include "GPX.hpp"
#include "ListOfCities.hpp"

using namespace std;

//tour -> map com o grafo
//unir os maps
//tirar as arestas repetidas e colocar o custo para 0
//encontrar as partiçṍes

int main(){
    vector<City> cities,cities2,vecList;

    vecList.push_back(City(1, 0.0, 3.0));
    vecList.push_back(City(2, 1.0, 3.0));
    vecList.push_back(City(3, 0.0, 2.0));
    vecList.push_back(City(4, 1.0, 2.0));
    vecList.push_back(City(5, 0.0, 1.0));
    vecList.push_back(City(6, 1.0, 1.0));
    vecList.push_back(City(7, 0.0, 0.0));
    vecList.push_back(City(8, 1.0, 0.0));

    ListOfCities listOfCities(vecList);

    cities.push_back(City(1, 0.0, 3.0));
    cities.push_back(City(2, 1.0, 3.0));
    cities.push_back(City(4, 1.0, 2.0));
    cities.push_back(City(6, 1.0, 1.0));
    cities.push_back(City(7, 0.0, 0.0));
    cities.push_back(City(8, 1.0, 0.0));
    cities.push_back(City(5, 0.0, 1.0));
    cities.push_back(City(3, 0.0, 2.0));

    cities2.push_back(City(1, 0.0, 3.0));
    cities2.push_back(City(2, 1.0, 3.0));
    cities2.push_back(City(3, 0.0, 2.0));
    cities2.push_back(City(5, 0.0, 1.0));
    cities2.push_back(City(7, 0.0, 0.0));
    cities2.push_back(City(8, 1.0, 0.0));
    cities2.push_back(City(6, 1.0, 1.0));
    cities2.push_back(City(4, 1.0, 2.0));

    Tour t(cities);
    Tour t2(cities2);

    map<int, CityNode*> map1 = mapTour(t), map2 = mapTour(t2);

    GPX objGXP;

    objGXP.joinGraphs(map1,map2,vecList);

    printMap(objGXP.unitedGraph);

    cout<<"------------------------------------------------------------------------------------------"<<endl;

    objGXP.cutCommonEdges();

    printMap(objGXP.unitedGraph);    

    objGXP.deleteMap(objGXP.unitedGraph);
    /* CityNode *root = mapVSF[1];
    deque<int> nextToVisit;
    vector<int> idAlreadyVisited;

    do{
        idAlreadyVisited.push_back(root->getId());
        for(CityNode::node p :  root->getEdges()){
            if(find(idAlreadyVisited.begin(),idAlreadyVisited.end(),p.first) == idAlreadyVisited.end()
                && 
            find(nextToVisit.begin(),nextToVisit.end(),p.first) == nextToVisit.end()){
                nextToVisit.push_back(p.first);
            }
        }
        if(!nextToVisit.empty()){
            root = mapVSF[nextToVisit.front()];
            nextToVisit.pop_front();
        }
        
    }while(!nextToVisit.empty()); */

}
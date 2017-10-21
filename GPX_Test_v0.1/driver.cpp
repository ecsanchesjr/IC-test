#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <deque>
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

/*     map<int, CityNode*>::iterator it = mapVSF.begin();

    while(it != mapVSF.end()){
        cout << " " << it->first << " | " << it->second->getId() << " " << endl;

        cout << "==========================" << endl;

        for(int i=0; i<2; i++){
            cout<<"edge "<<i<<": "<<mapVSF[it->second->getEdges().at(i).first]->getId();
            cout<<" distance: "<<it->second->getEdges().at(i).second<<endl;
        }
        it++;

        cout << "-----------------------------------------------------------------------------" << endl;
    } */

    CityNode *root = mapVSF[1];
    deque<int> nextToVisit;
    vector<int> idAlreadyVisited;

    do{
        idAlreadyVisited.push_back(root->getId());
        cout<<"id "<<root->getId()<<" colocado no vetor"<<endl;
        for(CityNode::node p :  root->getEdges()){
            if(find(idAlreadyVisited.begin(),idAlreadyVisited.end(),p.first) == idAlreadyVisited.end()
                && 
            find(nextToVisit.begin(),nextToVisit.end(),p.first) == nextToVisit.end()){
                nextToVisit.push_back(p.first);
                cout<<p.first<<" colocado na queue"<<endl;
            }
        }
        if(!nextToVisit.empty()){
            cout<<nextToVisit.front()<<" top of queue"<<endl;
            root = mapVSF[nextToVisit.front()];
            nextToVisit.pop_front();
        }
        
    }while(!nextToVisit.empty());

    for(int i : idAlreadyVisited){
        cout<<"id "<<i<<endl;
    }
}
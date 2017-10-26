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

    vecList.push_back(City(1, 0.0, 1.0));
    vecList.push_back(City(2, 0.0, 2.0));
    vecList.push_back(City(3, 1.0, 0.0));
    vecList.push_back(City(4, 1.0, 1.0));
    vecList.push_back(City(5, 1.0, 2.0));
    vecList.push_back(City(6, 1.0, 3.0));
    vecList.push_back(City(7, 2.0, 0.0));
    vecList.push_back(City(8, 2.0, 3.0)); 
    vecList.push_back(City(9, 3.0, 0.0)); 
    vecList.push_back(City(10, 3.0, 1.0)); 
    vecList.push_back(City(11, 3.0, 2.0)); 
    vecList.push_back(City(12, 2.0, 3.0)); 
    vecList.push_back(City(13, 4.0, 1.0)); 
    vecList.push_back(City(14, 4.0, 2.0)); 

    ListOfCities listOfCities(vecList);

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

    Tour t(cities);
    Tour t2(cities2);

    GPX::graphMap map1 = mapTour(t), map2 = mapTour(t2);
    //cout << "EOQ" << endl;
    GPX objGXP;

    objGXP.joinGraphs(map1,map2,vecList);
    //cout << "EOQ" << endl;
    //printMap(objGXP.unitedGraph);

    cout<<"------------------------------------------------------------------------------------------"<<endl;

    objGXP.cutCommonEdges();
    //cout << "EOQ" << endl;
    printMap(objGXP.unitedGraph);    
    //cout << "EOQ" << endl;
    /* vector<vector<CityNode>> eoq = objGXP.findPartitions(vecList);
    
    //cout << "EOQ" << endl;
    for(vector<CityNode> vcn : eoq){
        cout << "VETOR " << endl;
        for(CityNode cn : vcn){
            cout << cn.getId() << endl;
        }
    }
     */
    
    for(City c : listOfCities.getCitiesList()){
        objGXP.listOfCitiesWithGhosts.push_back(std::to_string(c.getId()));
    }
    objGXP.findAllPartitions();

    for(auto &part : objGXP.partitions){
        cout << part.second << endl;
    }

    /* if(objGXP.DFS_inside(3,6,map1)==GPX::IS_CONNECTED){
        cout<<"IS_CONNECTED"<<endl;
    }else{
        cout<<"IS_NOT_CONNECTED"<<endl;
    } */

    if(objGXP.DFS_outside("2")==GPX::CONNECTED_TO_PARTITION){
        cout<<"CONNECTED_TO_PARTITION"<<endl;
    }else{
        cout<<"CONNECTED_TO_SELF"<<endl;
    }

    if(objGXP.DFS_outside("3")==GPX::CONNECTED_TO_PARTITION){
        cout<<"CONNECTED_TO_PARTITION"<<endl;
    }else{
        cout<<"CONNECTED_TO_SELF"<<endl;
    }

    if(objGXP.DFS_outside("6")==GPX::CONNECTED_TO_PARTITION){
        cout<<"CONNECTED_TO_PARTITION"<<endl;
    }else{
        cout<<"CONNECTED_TO_SELF"<<endl;
    }

    if(objGXP.DFS_inside("3", "6", map1)==GPX::IS_CONNECTED){
        cout << "IS_CONNECTED" << endl;
    }else{
        cout << "IS_NOT_CONNECTED" << endl;
    }


    for(auto &part : objGXP.partitions){
        cout << part.second << endl;
    }

    // deletar pais
    objGXP.deleteMap(map1);
    objGXP.deleteMap(map2);

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
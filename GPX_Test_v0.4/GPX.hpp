#ifndef GPX_H
#define GPX_H

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <stack>
#include <string>

#include "CityNode.hpp"
#include "ListOfCities.hpp"
#include "Partition.hpp"
#include "City.hpp"

using std::string;
using std::to_string;
using std::stack;
using std::map;
using std::make_pair;
using std::find;
using std::deque;

class GPX {
public:
    typedef map<string, CityNode*> graphMap; 

    //mudar para ponteiro depois
    typedef map<int, Partition> partitionMap;

    enum searchResult { CONNECTED_TO_PARTITION,
        CONNECTED_TO_SELF,
        IS_CONNECTED,
        IS_NOT_CONNECTED };

    
    void joinGraphs(graphMap, graphMap, ListOfCities);
    void cutCommonEdges();
    vector<string> findPartition(const string);
    void findAllPartitions();

    int DFS_outside(string);
    int DFS_inside(string,string,graphMap);

    void checkPartitions();
    void deleteMap(graphMap);
    int whichPartition(const string);
    
    partitionMap partitions;
    graphMap unitedGraph;
    
    //precisamos da lista de todas as cidades
    //até mesmo as com ghosts
    vector<string> listOfCitiesWithGhosts;

private:
};

#endif
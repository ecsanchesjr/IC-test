#ifndef GPX_H
#define GPX_H

#include <map>
#include <iterator>
#include <algorithm>
#include <deque>

#include "CityNode.hpp"
#include "ListOfCities.hpp"

using std::map;
using std::make_pair;
using std::find;
using std::deque;

class GPX{
public:

    map<int, CityNode*> unitedGraph;
    void joinGraphs(map<int, CityNode*>,map<int, CityNode*>,ListOfCities);
    void cutCommonEdges();
    vector<vector<CityNode>> findPartitions(ListOfCities);

    void deleteMap(map<int,CityNode*>);
private:
};

#endif
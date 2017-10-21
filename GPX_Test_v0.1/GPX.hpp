#ifndef GPX_H
#define GPX_H

#include <map>
#include <iterator>

#include <algorithm>

#include "CityNode.hpp"
#include "ListOfCities.hpp"

using std::map;
using std::make_pair;
using std::find;

class GPX{
public:

    map<int, CityNode*> unitedGraph;
    void joinGraphs(map<int, CityNode*>,map<int, CityNode*>,ListOfCities);
    void cutCommonEdges();


    void deleteMap(map<int,CityNode*>);
private:
};

#endif
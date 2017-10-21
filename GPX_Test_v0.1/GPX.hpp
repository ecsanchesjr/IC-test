#ifndef GPX_H
#define GPX_H

#include <map>
#include <iterator>

#include "CityNode.hpp"

using std::map;
using std::make_pair;

class GPX{
public:
    void joinGraphs(map<int, CityNode*>,map<int, CityNode*>,Tour);
private:
    map<int, CityNode*> unitedGraph;
    void deleteMap(map<int,CityNode*>);
};

#endif
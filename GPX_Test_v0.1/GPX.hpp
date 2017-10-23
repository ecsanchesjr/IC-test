#ifndef GPX_H
#define GPX_H

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <stack>

#include "CityNode.hpp"
#include "ListOfCities.hpp"
#include "Partition.hpp"

using std::stack;
using std::map;
using std::make_pair;
using std::find;
using std::deque;

class GPX {
public:
    enum searchMode { INSIDE,
        OUTSIDE };
    enum searchResult { CONNECTED_TO_PARTITION,
        CONNETED_TO_SELF,
        IS_CONNECTED,
        IS_NOT_CONNECTED };

    map<int, CityNode*> unitedGraph;
    void joinGraphs(map<int, CityNode*>, map<int, CityNode*>, ListOfCities);
    void cutCommonEdges();
    vector<int> findPartition(const int);
    void findAllPartitions(ListOfCities&);

    pair<int, vector<int>> DFS(int id, vector<int> partition, int search);

    void checkPartitions();
    void deleteMap(map<int, CityNode*>);
    int wichPartition(const int);
    map<int, Partition> partitions;

private:
};

#endif
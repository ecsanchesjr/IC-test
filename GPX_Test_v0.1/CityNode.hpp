#ifndef CITYNODE_HPP
#define CITYNODE_HPP

#include <vector>
#include <utility>
#include <iostream>
#include "Tour.hpp"

using std::cout;
using std::endl;
using std::pair;
using std::vector;

class CityNode{
public:
    typedef pair<CityNode,double> node;    

    CityNode(int,Tour);

    int getId() const;
    vector<node>& getEdges();
    bool getAccess() const;

    void setId(int);
    void setEdges(vector<node>);
    void setAccess(bool);

    void addEdges(node);
    void deleteEdges(int);

private:
    int id;
    vector<node> edges;
    bool access;
};

#endif
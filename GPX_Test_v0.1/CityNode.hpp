#ifndef CITYNODE_HPP
#define CITYNODE_HPP

#include <vector>
#include <utility>
#include <iostream>
#include "Tour.hpp"
#include "City.hpp"

using std::cout;
using std::endl;
using std::pair;
using std::vector;

class CityNode{
public:
    typedef pair<CityNode*,double> node;    

    CityNode(int, double, double);

    int getId() const;
    double getX() const;
    double getY() const;
    vector<node>& getEdges();
    bool getAccess() const;

    void setId(int);
    void setX(double);
    void setY(double);
    void setEdges(vector<node>);
    void setAccess(bool);

    void addEdges(node);
    void deleteEdges(int);

private:
    int id;
    double x;
    double y;
    vector<node> edges;
    bool access;
};

#endif
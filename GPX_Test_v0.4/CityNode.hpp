#ifndef CITYNODE_HPP
#define CITYNODE_HPP

#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <algorithm>

#include "Tour.hpp"
#include "City.hpp"

using std::remove;
using std::cout;
using std::endl;
using std::string; 
using std::pair;
using std::vector;

class CityNode{
public:
    //estamos usando map, podemos usar ele para navegar o grafo
    //typedef pair<CityNode*,double> node;    

    //deixando o typedef assim então
    //int seria o ID, usando o id no map, podemos ir direto para o objeto
    typedef pair<string,double> node;        

    CityNode(string, double, double);

    string getId() const;
    double getX() const;
    double getY() const;
    vector<node>& getEdges();
    bool getAccess() const;

    void setId(string);
    void setX(double);
    void setY(double);
    void setEdges(vector<node>);
    void setAccess(bool);

    void addEdge(node);
    void deleteEdge(int);
    bool operator==(const CityNode&) const;

private:
    string id;
    double x;
    double y;
    vector<node> edges;
    bool access;
};

#endif
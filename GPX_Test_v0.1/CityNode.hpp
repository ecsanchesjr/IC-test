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
    //estamos usando map, podemos usar ele para navegar o grafo
    //typedef pair<CityNode*,double> node;    

    //deixando o typedef assim então
    //int seria o ID, usando o id no map, podemos ir direto para o objeto
    typedef pair<int,double> node;        

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

    bool operator==(const CityNode&) const;

private:
    int id;
    double x;
    double y;
    vector<node> edges;
    bool access;
};

#endif
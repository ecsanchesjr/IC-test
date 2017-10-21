#include "CityNode.hpp"

CityNode::CityNode(int id):id(id){
}

int CityNode::getId() const{return id;}

vector<CityNode::node>& CityNode::getEdges(){return edges;}

bool CityNode::getAccess() const{return access;}

void CityNode::setId(int id){this->id = id;}

void CityNode::setEdges(vector<node> edges){this->edges = edges;}

void CityNode::setAccess(bool access){this->access = access;}

void CityNode::addEdges(node e){
    edges.push_back(e);
}
void CityNode::deleteEdges(int i){
    if(i<=edges.size()){
        edges.erase(edges.begin()+i);
    }else{
        cout<<"ta apagando fora do limite pratinha"<<endl;
    }
}
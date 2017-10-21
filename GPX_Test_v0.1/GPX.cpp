#include "GPX.hpp"

void GPX::joinGraphs(map<int, CityNode*> father1, map<int, CityNode*> father2,Tour t){
    for(City c : t.getTour()){
        //criar a entrada no map da união
        unitedGraph.insert(make_pair(c.getId(),new CityNode(c.getId(),c.getX(),c.getY())));
        
        //colocar as edges no map da união
        for(CityNode::node n : father1[c.getId()]->getEdges()){
            unitedGraph[c.getId()]->addEdges(make_pair(n.first,n.second));
        }
        for(CityNode::node n : father2[c.getId()]->getEdges()){
            unitedGraph[c.getId()]->addEdges(make_pair(n.first,n.second));
        }
    }
    deleteMap(father1);
    deleteMap(father2);
}

void GPX::deleteMap(map<int, CityNode*>  m){
    for(map<int, CityNode*>::iterator it = m.begin();it!=m.end();it++){
        delete it->second;
    }
}
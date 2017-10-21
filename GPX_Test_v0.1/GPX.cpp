#include "GPX.hpp"

void GPX::joinGraphs(map<int, CityNode*> father1, map<int, CityNode*> father2,ListOfCities t){
    for(City c : t.getCitiesList()){
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

void GPX::cutCommonEdges(){
    for(map<int, CityNode*>::iterator it = unitedGraph.begin();it!=unitedGraph.end();it++){
        vector<CityNode::node> &vec = it->second->getEdges();
        for(int i=0;i<vec.size();i++){
            int commonEdges{0};
            int last{-1};
            for(int j=0;j<vec.size();j++){
                if(vec.at(i).first == vec.at(j).first){
                    commonEdges++;
                    last = j;
                    if(commonEdges>1){
                        vec.at(i).second = 0;
                        it->second->deleteEdges(last);
                        it->second->setAccess(true);
                    }
                }
            }
        }
    }
}

void GPX::deleteMap(map<int, CityNode*>  m){
    for(map<int, CityNode*>::iterator it = m.begin();it!=m.end();it++){
        delete it->second;
    }
}
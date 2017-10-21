#include "Utility.hpp"

double distance(City& c1, City& c2){
    return( sqrt( pow((c1.getX() - c2.getX()),2) + pow((c1.getX() - c2.getY()), 2) ) );
}

map<int, CityNode*> mapTour(Tour& t){
    //criar o map
    map<int,CityNode*> tmp;
    
    //criar os nós do grafo mas sem as referencias para os outros nós
    for(City c : t.getTour()){
        CityNode *cn = new CityNode(c.getId());
        tmp.insert(make_pair(c.getId(),cn));
    }

    //criar iterator do mapa
    map<int,CityNode*>::iterator it = tmp.begin();

    //arrumar as referências do grafo
    int j=0;
    while(it != tmp.end()){
        for(int i=0;i<t.getTour().size();i++){
            if(t.getTour().at(i).getId() == it->first){
                //prev
                if(i==0){
                    (*it->second).addEdges(make_pair(tmp[t.getTour().at(t.getTour().size()-1).getId()],distance(t.getTour().at(t.getTour().size()-1),t.getTour().at(j))));
                }else{
                    (*it->second).addEdges(make_pair(tmp[i-1],distance(t.getTour().at(i-1),t.getTour().at(j))));
                }
                //next
                if(i==t.getTour().size()-1){
                    (*it->second).addEdges(make_pair(tmp[0],distance(t.getTour().at(0),t.getTour().at(j))));
                }else{
                    (*it->second).addEdges(make_pair(tmp[i+1],distance(t.getTour().at(i+1),t.getTour().at(j))));
                }
            }
        }
        j++;
    }
}
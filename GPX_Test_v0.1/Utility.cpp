#include "Utility.hpp"

/* double distance(City& c1, City& c2){
    return( sqrt( pow((c1.getX() - c2.getX()),2) + pow((c1.getX() - c2.getY()), 2) ) );
} */

double distance(double x1, double y1, double x2, double y2){
    return( sqrt( pow((x1-x2),2) + pow((y1-y2),2) ) );
}

map<int, CityNode*> mapTour(Tour& t){  // Mapear o tour para um grafo com ligações entre os nós

    if(t.getTour().empty()){
        exit(0);
    }

    map<int, CityNode*> aux; // Mapa com as conexões dos nodes
    double dist = 0;
    vector<City> cities{t.getTour()};

    CityNode *prev = new CityNode(cities.at(0).getId(), cities.at(0).getX(), cities.at(0).getY()); // ponto anterior ao atual dentro do for
    CityNode *first = prev; // referência do primeiro acesso

    aux.insert(make_pair(first->getId(), first) );  // gera o mapa e insere o primeiro dentro dele
    
    for(int i=1; i<t.getTour().size(); i++){ // percorre o vetor a partir do segundo elemento, o primeiro já foi transformado
        CityNode *cn = new CityNode(cities.at(i).getId(), cities.at(i).getX(), cities.at(i).getY()); // gera um node com o segundo elemento

        aux.insert(make_pair(cn->getId(), cn) ); // insere o node dentro do mapa
        dist = distance(prev->getX(), prev->getY(), cn->getX(), cn->getY() ) ;
        cn->addEdges(CityNode::node(prev->getId(), dist) ); // adiciona ao node atual as arestas de conexão 
        
        dist = distance(cn->getX(), cn->getY(), prev->getX(), prev->getY() );
        prev->addEdges(CityNode::node(cn->getId(), dist ) );  // adiciona ao node anterior o atual como um próx (lista duplamente encadeada)
        
        prev = cn; // o anterior recebe o atual para continuar o for
    }

    dist =  distance(prev->getX(), prev->getY() , first->getX(), first->getY() );
    first->addEdges(CityNode::node(prev->getId(),dist ) ); // o primeiro recebe o atual ao sair do for, completando os ligamentos das arestas
    
    dist = distance(first->getX(), first->getY(), prev->getX(), prev->getY());
    prev->addEdges(CityNode::node(first->getId(), dist ) );  // o atual recebe o primeiro para completar os ligamentos
 
    return(aux);  // retorna o mpaa com os nodes já instanciados e adicionados
}

void printMap(map<int, CityNode*> &m){
    for(map<int, CityNode*>::iterator it = m.begin(); it != m.end(); it++){
        cout << " " << it->first << " | " << it->second->getId() << endl;
        cout<<"Acess: "<<it->second->getAccess()<<endl;
        cout << "===============================" << endl;

        for(int i=0; i<it->second->getEdges().size(); i++){
            cout << "Edge: " << i << " : " << m[it->second->getEdges().at(i).first]->getId();
            cout << " # ";
            cout << "Distance: " << it->second->getEdges().at(i).second << endl;
        }
        cout << "----------------------------------" << endl;
        cout << endl;
    }
}
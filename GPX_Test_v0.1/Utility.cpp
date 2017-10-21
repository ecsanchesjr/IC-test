#include "Utility.hpp"

/* double distance(City& c1, City& c2){
    return( sqrt( pow((c1.getX() - c2.getX()),2) + pow((c1.getX() - c2.getY()), 2) ) );
} */

double distance(double x1, double y1, double x2, double y2){
    return( sqrt( pow((x1-x2),2) + pow((y1-y2),2) ) );
}

map<int, CityNode*> mapTour(Tour& t){  // Mapear o tour para um grafo com ligações entre os nós

    map<int, CityNode*> aux; // Mapa com as conexões dos nodes

    vector<City> cities{t.getTour()};

    CityNode *prev = new CityNode(cities.at(0).getId(), cities.at(0).getX(), cities.at(0).getY()); // ponto anterior ao atual dentro do for
    CityNode *first = prev; // referência do primeiro acesso

    aux.insert(make_pair(first->getId(), first) );  // gera o mapa e insere o primeiro dentro dele
    
    for(int i=1; i<t.getTour().size(); i++){ // percorre o vetor a partir do segundo elemento, o primeiro já foi transformado
        CityNode *cn = new CityNode(cities.at(i).getId(), cities.at(i).getX(), cities.at(i).getY()); // gera um node com o segundo elemento

        aux.insert(make_pair(cn->getId(), cn) ); // insere o node dentro do mapa

        cn->addEdges(CityNode::node(prev, distance(prev->getX(), prev->getY(), cn->getX(), cn->getY() ) ) ); // adiciona ao node atual as arestas de conexão 
        
        prev->addEdges(CityNode::node(cn, distance(cn->getX(), cn->getY(), prev->getX(), prev->getY() ) ) );  // adiciona ao node anterior o atual como um próx (lista duplamente encadeada)
        
        prev = cn; // o anterior recebe o atual para continuar o for
    }

    first->addEdges(CityNode::node(prev, distance(prev->getX(), prev->getY() , first->getX(), first->getY() ) ) ); // o primeiro recebe o atual ao sair do for, completando os ligamentos das arestas
    
    prev->addEdges(CityNode::node(first, distance(first->getX(), first->getY(), prev->getX(), prev->getY()) ) );  // o atual recebe o primeiro para completar os ligamentos
 
    return(aux);  // retorna o mpaa com os nodes já instanciados e adicionados
}
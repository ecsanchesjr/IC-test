#include "GPX.hpp"

void GPX::joinGraphs(
    map<int, CityNode*> father1, map<int, CityNode*> father2,
    ListOfCities t)
{ // executa a união dos dois grafos, gerando Gu
    for (City c : t.getCitiesList()) {
        // criar a entrada no map da união
        unitedGraph.insert(
            make_pair(c.getId(), new CityNode(c.getId(), c.getX(), c.getY())));

        // colocar as edges no map da união
        for (CityNode::node n : father1[c.getId()]->getEdges()) {
            unitedGraph[c.getId()]->addEdges(make_pair(n.first, n.second));
        }
        for (CityNode::node n : father2[c.getId()]->getEdges()) {
            unitedGraph[c.getId()]->addEdges(make_pair(n.first, n.second));
        }
    }
    // deletar pais
    deleteMap(father1);
    deleteMap(father2);
}

void GPX::cutCommonEdges()
{ // executa o processo de "cortar" as arestas iguais
    // entre os pais, a partir do grafo da união,
    // gerando o Gu'
    for (map<int, CityNode*>::iterator it = unitedGraph.begin();
         it != unitedGraph.end(); it++) { // percorre todas as entradas do Gu

        vector<CityNode::node>& vec = it->second->getEdges(); // Carrega o vetor com as arestas contidas
        // naquela entrada do mapa

        for (int i = 0; i < vec.size(); i++) { // percorre o vetor de arestas

            int commonEdges{ 0 }; // contagem de vértices iguais, caso contenha dois
            // iguais será executado um "corte"

            int last{ -1 }; // posição da primeira instância do no repetido

            for (int j = 0; j < vec.size(); j++) { // percorre o vetor de arestas

                if (vec.at(i).first == vec.at(j).first) { // verifica igualdade
                    commonEdges++;
                    last = j;

                    if (commonEdges > 1) { // caso exista mais do que uma instância do
                        // vértice então executa o corte

                        vec.at(i).second = 0; // Distância entre os vértices = 0 para simbolizar o corte
                        it->second->deleteEdges(
                            last); // Deleta a primeira instância do vértice
                        it->second->setAccess(
                            true); // Altera o acesso do vértice (entrada e saída)
                    }
                }
            }
        }
    }
}

vector<int> GPX::findPartition(const int nodeOne)
{ // a partir do valor passado
    // irá executar uma busca em
    // Gu' para encontrar as
    // partições
    // nodeOne funciona como uma raiz, que será o ponto inicial da busca, achando
    // a partição onde ele está contido
    // retorna um vetor com os IDs das cidades que compoem a partição

    CityNode* root; // nó para verificação
    vector<int> idAlreadyVisited; // lista dos nós já visitados
    deque<int> nextToVisit; // lista dos próximos a visitar

    vector<int> partition;

    bool notAlreadyVisited{ false };
    bool notToVisit{ false };
    bool notCut{ false };

    nextToVisit.push_back(nodeOne); // primeiro a ser visitado

    while (!nextToVisit.empty()) { // enquanto a não for vazio

        root = unitedGraph[nextToVisit.front()]; // raiz para execução

        nextToVisit.pop_front(); // após "pegar" para execução, limpar o nó da lista

        partition.push_back(root->getId()); // coloca o nó na partição

        idAlreadyVisited.push_back(root->getId()); // Nó na lista de "já visitados"

        for (CityNode::node n :
            root->getEdges()) { // irá percorrer as arestas ligadas

            notAlreadyVisited = find(idAlreadyVisited.begin(), idAlreadyVisited.end(), n.first) == idAlreadyVisited.end(); // verificar se a aresta não foi visitada

            notToVisit = find(nextToVisit.begin(), nextToVisit.end(), n.first) == nextToVisit.end(); // verificar se não está na lista para ser visitada

            notCut = n.second != 0; // verificar se ela não foi cortada

            if (notAlreadyVisited && notToVisit && notCut) { // caso todas as condições estejam TRUE

                nextToVisit.push_back(
                    n.first); // coloca na lista dos proximos a serem visitados
            }
        }
    }
    return (partition); // retornar vetor com IDs da partição
}

vector<vector<int>>
GPX::findAllPartitions(ListOfCities& citiesList)
{ // irá percorrer todo o grafo
    // encotrando as partições
    // presentes nele

    vector<vector<int>> partitions;
    vector<City> cities = citiesList.getCitiesList();

    while (!cities.empty()) { // enquanto a lista de cidades ainda existir

        partitions.push_back(findPartition(
            cities.front()
                .getId())); // insere o retorno da função na lista de partições

        for (int i : partitions.back()) { // percorre a última partição

            for (int j = 0; j < cities.size(); j++) { // percorre a lista de cidades

                if (i == cities.at(j).getId()) { // se a cidade estiver na última partição

                    cities.erase(cities.begin() + j); // apagar a cidade da lista
                }
            }
        }
    }

    for (int i = 0; i < partitions.size();
         i++) { // retirar partições com tamanho 1
        if (partitions[i].size() == 1) {
            partitions.erase(
                remove(partitions.begin(), partitions.end(), partitions[i]),
                partitions.end());
            i--;
        }
    }

    return (partitions); // retornar a lista de partições
}

void GPX::deleteMap(map<int, CityNode*> m)
{ // deletar o mapa completamente,
    // desalocando os ponteiros tb

    for (map<int, CityNode*>::iterator it = m.begin(); it != m.end(); it++) {
        delete it->second;
    }
}

void GPX::checkPartition() {}
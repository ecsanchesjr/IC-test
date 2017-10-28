#ifndef GPX2_HPP
#define GPX2_HPP

#include <algorithm>
#include <deque>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <string>

#include "City.hpp"
#include "CityNode.hpp"
#include "ListOfCities.hpp"
#include "Partition.hpp"

using std::string;
using std::to_string;
using std::stack;
using std::map;
using std::make_pair;
using std::find;
using std::deque;
using std::set;

typedef map<string, CityNode*> cityMap;
//mudar para ponteiro depois
typedef map<int, Partition> partitionMap;

enum searchResult { CONNECTED_TO_PARTITION,
    CONNECTED_TO_SELF,
    IS_CONNECTED,
    IS_NOT_CONNECTED };

vector<string> CityToString(vector<City>);
int DFS_inside(string, string, cityMap, Partition, vector<string>&);
int DFS_outside(string, cityMap, partitionMap);
void joinGraphs(cityMap&, cityMap&, cityMap&);
void cutCommonEdges(cityMap&);
vector<string> findPartition(const string, cityMap);
void findAllPartitions(cityMap, partitionMap&);
void deleteMap(cityMap&);
cityMap mapToTour(Tour&);
double distance(double, double, double, double);
void printMap(cityMap&);
int whichPartition(const string, partitionMap);

void eraseSubVector(vector<string>&, vector<string>&);

void cleanInsideAccess(cityMap, partitionMap&);

void checkAllPartitions(cityMap, cityMap, cityMap&, partitionMap&);
bool checkPartition(cityMap, cityMap, cityMap&, Partition&);

void createGhosts(cityMap&, cityMap&);
void insertGhost(string&, cityMap&, CityNode*);

//mudar para Tour depois, quando estiver gerando o resultado do crossover
void GPX2(Tour red, Tour blue)
{
    partitionMap allPartitions;
    cityMap unitedGraph;

    //pegar lista de todas as cidades existentes no tour
    //vector<City> cityList = red.getTour();

    //precisamos da lista de todas as cidades
    //até mesmo as com ghosts
    //vector<string> listOfCitiesWithGhosts = CityToString(cityList);

    //Tour to graph
    cityMap redMap = mapToTour(red);
    cityMap blueMap = mapToTour(blue);

    cout << "RED MAP" << endl;
    printMap(redMap);
    cout << "-------------------------------------------------" << endl;
    cout << "BLUE MAP" << endl;
    printMap(blueMap);
    cout << "-------------------------------------------------" << endl;

    createGhosts(redMap, blueMap);
    cout << "RED MAP" << endl;
    printMap(redMap);
    cout << "-------------------------------------------------" << endl;
    cout << "BLUE MAP" << endl;
    printMap(blueMap);
    cout << "-------------------------------------------------" << endl;

    //merge maps
    joinGraphs(redMap, blueMap, unitedGraph);
    /* cout << "UNITED GRAPH" << endl;
    printMap(unitedGraph);
    cout << "-------------------------------------------------" << endl; */

    //cut common edges in unitedGraph
    cutCommonEdges(unitedGraph);
    /* cout << "CUT GRAPH" << endl;
    printMap(unitedGraph);
    cout << "-------------------------------------------------" << endl; */

    //create ghosts vertices
    //createGhosts(redMap, blueMap);

    cout << "RED MAP" << endl;
    printMap(redMap);
    cout << "-------------------------------------------------" << endl;
    cout << "BLUE MAP" << endl;
    printMap(blueMap);
    cout << "-------------------------------------------------" << endl;
    cout << "AFTER CREATE GHOSTS GRAPH" << endl;
    printMap(unitedGraph);
    cout << "-------------------------------------------------" << endl;

    //find partitions on unitedGraph
    findAllPartitions(unitedGraph, allPartitions);

    cout << "ALL PARTITIONS" << endl;
    for (auto& part : allPartitions) {
        cout << part.second << endl;
    }
    cout << "-------------------------------------------------" << endl;

    cleanInsideAccess(unitedGraph, allPartitions);

    cout << "ALL PARTITIONS 1" << endl;
    for (auto& part : allPartitions) {
        cout << part.second << endl;
    }
    cout << "-------------------------------------------------" << endl;

    checkAllPartitions(redMap, blueMap, unitedGraph, allPartitions);

    cout << "ALL PARTITIONS 2" << endl;
    for (auto& part : allPartitions) {
        cout << part.second << endl;
    }
    cout << "-------------------------------------------------" << endl;

    //deletar os mapas
    deleteMap(redMap);
    deleteMap(blueMap);

    deleteMap(unitedGraph);
}

vector<string> CityToString(vector<City> cityList)
{
    vector<string> tmp;
    for (City c : cityList) {
        tmp.push_back(to_string(c.getId()));
    }
    return tmp;
}

void cleanInsideAccess(cityMap unitedGraph, partitionMap& allPartitions)
{
    for (auto& p : allPartitions) {
        vector<string> tmp;
        for (string id : p.second.getAccessNodes()) {
            if (DFS_outside(id, unitedGraph, allPartitions) == CONNECTED_TO_PARTITION) {
                tmp.push_back(id);
            }
        }
        p.second.setAccessNodes(tmp);
    }
}

int DFS_inside(string entry, string exit, cityMap father, Partition partitionObj, vector<string>& returnVector)
{
    string now;
    vector<string> alreadyVisited;
    deque<string> nextToVisit;
    vector<string> partition = partitionObj.getNodes();
    bool notAlreadyVisited{ false };
    bool notToVisit{ false };
    bool notExit{ false };

    alreadyVisited.push_back(entry);

    for (CityNode::node cn : father[entry]->getEdges()) {
        //pega o nó que está dentro da partição
        if (find(partition.begin(), partition.end(), cn.first) != partition.end()) {
            nextToVisit.push_back(cn.first);
            break;
        }
    }

    while (!nextToVisit.empty()) {

        now = nextToVisit.back();
        nextToVisit.pop_back();
        alreadyVisited.push_back(now);
        vector<CityNode::node> edges = father[now]->getEdges();

        for (CityNode::node cn : edges) {

            notAlreadyVisited = (find(alreadyVisited.begin(), alreadyVisited.end(), cn.first) == alreadyVisited.end());
            notToVisit = (find(nextToVisit.begin(), nextToVisit.end(), cn.first) == nextToVisit.end());
            notExit = cn.first != exit;

            if (notAlreadyVisited && notToVisit && notExit) {
                nextToVisit.push_back(cn.first);
            }
            if (!notExit) {
                alreadyVisited.push_back(cn.first);
            }
        }
    }
    /* cout<<"already visited"<<endl;
    for(int i : alreadyVisited){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"last node visited "<<alreadyVisited.back()<<" exit "<<exit<<endl; */
    returnVector = alreadyVisited;
    return (alreadyVisited.back() == exit ? IS_CONNECTED : IS_NOT_CONNECTED);
}

int DFS_outside(string id, cityMap unitedGraph, partitionMap allPartitions)
{
    string now;
    int idPartition = whichPartition(id, allPartitions);
    vector<string> partition = allPartitions[idPartition].getNodes();
    vector<string> alreadyVisited;
    deque<string> nextToVisit;
    int partitionConnected{ -1 };
    bool notAlreadyVisited{ false };
    bool notToVisit{ false };
    bool cutEdge{ false };

    nextToVisit.push_back(id);

    /* for (CityNode::node cn : unitedGraph[id]->getEdges()) {
        //percorrer pela aresta que tem custo zero
        if (cn.second == 0) {
            cout<<"id "<<id<<endl;
            cout<<"next to visit: "<<cn.first<<endl;
            nextToVisit.push_back(cn.first);
            break;
        }
    } */
    /* cout<<"new DFS"<<endl; */
    while (!nextToVisit.empty()) {
        /* cout<<"nextToVisit ";
        for(string s : nextToVisit){
            cout<<s<<" ";
        }
        cout<<endl; */
        now = nextToVisit.back();
        nextToVisit.pop_back();

        alreadyVisited.push_back(now);

        vector<CityNode::node> edges = unitedGraph[now]->getEdges();

        /* cout<<"now "<<now<<endl; */

        for (CityNode::node cn : edges) {
            notAlreadyVisited = (find(alreadyVisited.begin(), alreadyVisited.end(), cn.first) == alreadyVisited.end());
            notToVisit = (find(nextToVisit.begin(), nextToVisit.end(), cn.first) == nextToVisit.end());
            cutEdge = cn.second == 0;

            if (notAlreadyVisited && notToVisit && cutEdge) {
                /* cout<<"next to visit "<<cn.first<<endl;
                 */ nextToVisit.push_back(cn.first);
            }
        }
    }

    //pegar o id da partition do nó que passou por último
    partitionConnected = whichPartition(alreadyVisited.back(), allPartitions);

    /* //not already in connected list
    if (find(
            partitions[idPartition].getConnectedTo().begin(),
            partitions[idPartition].getConnectedTo().end(),
            partitionConnected)
        == partitions[idPartition].getConnectedTo().end()) {
        partitions[idPartition].getConnectedTo().push_back(partitionConnected);
    } */
    //connectado nele mesmo
    if (idPartition == partitionConnected) {
        //se conectar em si mesmo, seta o nó de entrada e o ultimo onde chegou como não access
        unitedGraph[id]->setAccess(false);
        unitedGraph[alreadyVisited.back()]->setAccess(false);
        return CONNECTED_TO_SELF;
    } else {
        //partitions[idPartition].getConnectedTo().push_back(partitionConnected);
        return CONNECTED_TO_PARTITION;
    }
}

void joinGraphs(
    cityMap& red, cityMap& blue, cityMap& unitedGraph)
{ // executa a união dos dois grafos, gerando Gu
    vector<string> cityList;
    for (auto node : red) {
        cityList.push_back(node.first);
    }
    for (string id : cityList) {
        CityNode* c = red[id];
        // criar a entrada no map da união
        unitedGraph.insert(
            make_pair((c->getId()), new CityNode((c->getId()), c->getX(), c->getY())));

        // colocar as edges no map da união
        for (CityNode::node n : red[(c->getId())]->getEdges()) {
            unitedGraph[(c->getId())]->addEdge(make_pair(n.first, n.second));
        }
        for (CityNode::node n : blue[(c->getId())]->getEdges()) {
            unitedGraph[(c->getId())]->addEdge(make_pair(n.first, n.second));
        }
    }
}

void cutCommonEdges(cityMap& unitedGraph)
{ // executa o processo de "cortar" as arestas iguais
    // entre os pais, a partir do grafo da união,
    // gerando o Gu'
    for (cityMap::iterator it = unitedGraph.begin();
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
                        it->second->deleteEdge(
                            last); // Deleta a primeira instância do vértice
                        it->second->setAccess(
                            true); // Altera o acesso do vértice (entrada e saída)
                    }
                }
            }
        }
    }
}

vector<string> findPartition(const string nodeOne, cityMap unitedGraph)
{ // a partir do valor passado
    // irá executar uma busca em
    // Gu' para encontrar as
    // partições
    // nodeOne funciona como uma raiz, que será o ponto inicial da busca, achando
    // a partição onde ele está contido
    // retorna um vetor com os IDs das cidades que compoem a partição

    CityNode* root; // nó para verificação
    vector<string> idAlreadyVisited; // lista dos nós já visitados
    deque<string> nextToVisit; // lista dos próximos a visitar

    vector<string> partition;

    bool notAlreadyVisited{ false };
    bool notToVisit{ false };
    bool notCut{ false };

    nextToVisit.push_back(nodeOne); // primeiro a ser visitado

    while (!nextToVisit.empty()) { // enquanto a não for vazio

        root = unitedGraph[nextToVisit.front()]; // raiz para execução

        cout << "now id " << root->getId() << endl;

        nextToVisit.pop_front(); // após "pegar" para execução, limpar o nó da lista

        partition.push_back(root->getId()); // coloca o nó na partição

        idAlreadyVisited.push_back(root->getId()); // Nó na lista de "já visitados"

        for (CityNode::node n :
            root->getEdges()) { // irá percorrer as arestas ligadas

            notAlreadyVisited = find(idAlreadyVisited.begin(), idAlreadyVisited.end(), n.first) == idAlreadyVisited.end(); // verificar se a aresta não foi visitada

            notToVisit = find(nextToVisit.begin(), nextToVisit.end(), n.first) == nextToVisit.end(); // verificar se não está na lista para ser visitada

            notCut = n.second != 0; // verificar se ela não foi cortada

            if (notAlreadyVisited && notToVisit && notCut) { // caso todas as condições estejam TRUE
                cout << "next to visit " << n.first << endl;
                nextToVisit.push_back(
                    n.first); // coloca na lista dos proximos a serem visitados
            }
        }
    }
    return (partition); // retornar vetor com IDs da partição
}

void findAllPartitions(cityMap unitedGraph, partitionMap& allPartitions)
{ // irá percorrer todo o grafo
    // encotrando as partições
    // presentes nele
    int id{ 1 };
    vector<vector<string>> partitions;
    vector<string> cities;

    //pegar a lista de todas as cidades
    for (auto node : unitedGraph) {
        cities.push_back(node.first);
    }

    while (!cities.empty()) { // enquanto a lista de cidades ainda existir

        partitions.push_back(findPartition(cities.front(), unitedGraph)); // insere o retorno da função na lista de partições

        /* for (string i : partitions.back()) { // percorre a última partição

            for (int j = 0; j < cities.size(); j++) { // percorre a lista de cidades

                if (i == cities.at(j).getId()) { // se a cidade estiver na última partição

                    cities.erase(cities.begin() + j); // apagar a cidade da lista
                }
            }
        } */

        for (string i : partitions.back()) {
            cities.erase(remove(cities.begin(), cities.end(), i), cities.end());
        }
    }

    for (vector<string> vi : partitions) { // retirar partições com tamanho 1
        if (vi.size() != 1) {
            vector<string> accessNodes;
            for (string id : vi) {
                if (unitedGraph[id]->getAccess()) {
                    accessNodes.push_back(id);
                }
            }
            allPartitions.insert(make_pair(id, Partition(id, vi, accessNodes)));
            id++;
        }
    }
}

void deleteMap(cityMap& m)
{ // deletar o mapa completamente,
    // desalocando os ponteiros tb

    for (cityMap::iterator it = m.begin(); it != m.end(); it++) {
        delete it->second;
    }
}

void checkAllPartitions(cityMap red, cityMap blue, cityMap& unitedGraph, partitionMap& allPartitions)
{
    //verifica todas as partições
    for (auto p : allPartitions) {
        //se não for uma partição recombinante ele deleta da lista de partições
        if (!checkPartition(red, blue, unitedGraph, p.second)) {
            allPartitions.erase(p.first);
        }
    }
}

bool checkPartition(cityMap red, cityMap blue, cityMap& unitedGraph, Partition& partition)
{
    unsigned size = partition.getAccessNodes().size();
    vector<string> redNodes, blueNodes;
    redNodes = blueNodes = partition.getNodes();
    if (!(size % 2 == 0)) {
        //não é uma partição recombinante pois não possui uma entrada para cada saida.
        return (false);
    } else {
        vector<string> nodesInPartition = partition.getNodes();
        bool foundExit{ false };
        pair<string, string> access;
        for (unsigned i = 0; i < size / 2; i++) {
            //encontrando entrada e saida no red e verifica se elas existem
            access.first = partition.getAccessNodes()[0];
            bool foundConnected{ false };
            for (unsigned j = 1; j < size; j++) {
                vector<string> nodesVisited;
                if (DFS_inside(access.first, partition.getAccessNodes()[j], red, partition, nodesVisited) == IS_CONNECTED) {
                    access.second = partition.getAccessNodes()[j];
                    foundConnected = true;
                    eraseSubVector(redNodes, nodesVisited);

                    break;
                }
            }
            if (!foundConnected) {
                return (false);
            }
            //verifica no blue se os mesmos pontos de entrada e saida funcionam
            {
                vector<string> nodesVisited;
                if (DFS_inside(access.first, access.second, blue, partition, nodesVisited) == IS_CONNECTED) {
                    eraseSubVector(blueNodes, nodesVisited);
                } else {
                    //a entrada e saida encontrada no red não funciona no blue também
                    return (false);
                }
            }
        }
        //depois de encontrar todas as entradas e saidas, é necessário verificar se todos os nós da partição foram percorridos pelos dois pais
        if (redNodes.empty() && blueNodes.empty()) {
            return (true);
        } else {
            return (false);
        }
    }
}

int whichPartition(const string id, partitionMap allPartitions)
{ // Procura em qual partição está a cidade procurada, retorna o ID da partição
    for (auto& p : allPartitions) {
        if (find(p.second.getNodes().begin(), p.second.getNodes().end(), id) != p.second.getNodes().end()) {
            return (p.first);
        }
    }
    return (-1);
}

cityMap mapToTour(Tour& t)
{ // Mapear o tour para um grafo com ligações entre os nós

    if (t.getTour().empty()) {
        exit(0);
    }

    map<string, CityNode*> aux; // Mapa com as conexões dos nodes
    double dist = 0;
    vector<City> cities{ t.getTour() };

    CityNode* prev = new CityNode(to_string(cities.at(0).getId()), cities.at(0).getX(), cities.at(0).getY()); // ponto anterior ao atual dentro do for
    CityNode* first = prev; // referência do primeiro acesso

    aux.insert(make_pair(first->getId(), first)); // gera o mapa e insere o primeiro dentro dele

    for (int i = 1; i < t.getTour().size(); i++) { // percorre o vetor a partir do segundo elemento, o primeiro já foi transformado
        CityNode* cn = new CityNode(to_string(cities.at(i).getId()), cities.at(i).getX(), cities.at(i).getY()); // gera um node com o segundo elemento

        aux.insert(make_pair(cn->getId(), cn)); // insere o node dentro do mapa
        dist = distance(prev->getX(), prev->getY(), cn->getX(), cn->getY());
        cn->addEdge(CityNode::node(prev->getId(), dist)); // adiciona ao node atual as arestas de conexão

        dist = distance(cn->getX(), cn->getY(), prev->getX(), prev->getY());
        prev->addEdge(CityNode::node(cn->getId(), dist)); // adiciona ao node anterior o atual como um próx (lista duplamente encadeada)

        prev = cn; // o anterior recebe o atual para continuar o for
    }

    dist = distance(prev->getX(), prev->getY(), first->getX(), first->getY());
    first->addEdge(CityNode::node(prev->getId(), dist)); // o primeiro recebe o atual ao sair do for, completando os ligamentos das arestas

    dist = distance(first->getX(), first->getY(), prev->getX(), prev->getY());
    prev->addEdge(CityNode::node(first->getId(), dist)); // o atual recebe o primeiro para completar os ligamentos

    return (aux); // retorna o mpaa com os nodes já instanciados e adicionados
}

void createGhosts(cityMap& red, cityMap& blue)
{
    set<string> isGhost;
    // The SET containner does not allow repeated values inside yourself

    for (auto& city : red) {

        string idKey = city.first;
        if (idKey.find("-") == string::npos) { // the node is not a ghost

            for (unsigned i = 0; i < 2; i++) {
                isGhost.insert(city.second->getEdges()[i].first);
                isGhost.insert(blue[idKey]->getEdges()[i].first);
            }

            if (isGhost.size() == 4) { // node with degree 4
                cout << "Grau 4" << endl;
                string ghostID = idKey + "-";
                double x = city.second->getX(), y = city.second->getY();

                CityNode* ghostNode = new CityNode(ghostID, x, y);
                insertGhost(idKey, red, ghostNode);

                ghostNode = new CityNode(ghostID, x, y);
                insertGhost(idKey, blue, ghostNode);
            }

            isGhost.clear();
        }
    }
}

void insertGhost(string& id, cityMap& tour, CityNode* ghost)
{
    CityNode::node edgeFirst = tour[id]->getEdges()[0]; // edge que será mandado para o ghost
    tour[id]->deleteEdge(0); // delete edge
    tour[id]->addEdge(CityNode::node(ghost->getId(), 0)); // adiciona ao node "REAL" o edge de ligação com o ghost

    for (unsigned i=0; i<2; i++) {
        // percorre os edges de ligação com o nó que foi para o ghost
        CityNode::node edge = tour[edgeFirst.first]->getEdges()[i];

        if (edge.first.compare(id) == 0) { // verifica se é a ligação

            // adiciona a ligação ao ghost e deleta do "REAL"
            double distTmp = edge.second;

            tour[edgeFirst.first]->deleteEdge(i);
            tour[edgeFirst.first]->addEdge(CityNode::node(ghost->getId(), edgeFirst.second));
        }
    }

    ghost->addEdge(edgeFirst); // faz o ghost se ligar ao edge
    ghost->setAccess(true);
    ghost->addEdge(CityNode::node(tour[id]->getId(), 0)); // adiciona o REAL como um edge do ghost

    tour.insert(make_pair(ghost->getId(), ghost));  // insere o ghost no mapPai
}

void printMap(cityMap& m)
{
    for (map<string, CityNode*>::iterator it = m.begin(); it != m.end(); it++) {
        cout << " " << it->first << " | " << it->second->getId() << endl;
        cout << "Acess: " << it->second->getAccess() << endl;
        cout << "==================================" << endl;

        for (int i = 0; i < it->second->getEdges().size(); i++) {
            cout << "Edge " << i << ": " << m[it->second->getEdges().at(i).first]->getId();
            cout << "\t#\t";
            cout << "Distance: " << it->second->getEdges().at(i).second << endl;
        }
        cout << "----------------------------------" << endl;
        cout << endl;
    }
}

double distance(double x1, double y1, double x2, double y2)
{
    return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}

void eraseSubVector(vector<string>& vec, vector<string>& subvec)
{
    for (unsigned i = 0; i < subvec.size(); i++) {
        for (unsigned j = 0; vec.size(); j++) {
            if (subvec[i].compare(vec[j]) == 0) {
                vec.erase(vec.begin() + j);
                break;
            }
        }
    }
}

#endif
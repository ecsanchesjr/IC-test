/* #include "GPX.hpp"

int GPX::DFS_inside(string entry, string exit, graphMap father)
{
    string now;
    vector<string> alreadyVisited;
    deque<string> nextToVisit;
    int entryPartition = whichPartition(entry);
    vector<string> partition = partitions[entryPartition].getNodes();
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
            if(!notExit){
                alreadyVisited.push_back(cn.first);
            }
        }
    }
    /* cout<<"already visited"<<endl;
    for(int i : alreadyVisited){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"last node visited "<<alreadyVisited.back()<<" exit "<<exit<<endl; 
    return (alreadyVisited.back() == exit ? IS_CONNECTED : IS_NOT_CONNECTED);
}

int GPX::DFS_outside(string id)
{
    string now;
    int idPartition = whichPartition(id);
    vector<string> partition = partitions[idPartition].getNodes();
    vector<string> alreadyVisited;
    deque<string> nextToVisit;
    int partitionConnected{ -1 };
    bool notAlreadyVisited{ false };
    bool notToVisit{ false };
    bool isNotAccess{ false };

    alreadyVisited.push_back(id);

    for (CityNode::node cn : unitedGraph[id]->getEdges()) {
        //pega o nó que está fora da partição
        if (find(partition.begin(), partition.end(), cn.first) == partition.end()) {
            nextToVisit.push_back(cn.first);
            break;
        }
    }

    while (!nextToVisit.empty()) {
        now = nextToVisit.back();
        nextToVisit.pop_back();
        alreadyVisited.push_back(now);
        vector<CityNode::node> edges = unitedGraph[now]->getEdges();
        for (CityNode::node cn : edges) {
            notAlreadyVisited = (find(alreadyVisited.begin(), alreadyVisited.end(), cn.first) == alreadyVisited.end());
            notToVisit = (find(nextToVisit.begin(), nextToVisit.end(), cn.first) == nextToVisit.end());
            isNotAccess = unitedGraph[cn.first]->getAccess();
            if (notAlreadyVisited && notToVisit && isNotAccess) {
                nextToVisit.push_back(cn.first);
            }
            if (!isNotAccess) {
                alreadyVisited.push_back(cn.first);
            }
        }
    }

    //pegar o id da partition do nó que passou por último
    partitionConnected = whichPartition(alreadyVisited.back());

    /* //not already in connected list
    if (find(
            partitions[idPartition].getConnectedTo().begin(),
            partitions[idPartition].getConnectedTo().end(),
            partitionConnected)
        == partitions[idPartition].getConnectedTo().end()) {
        partitions[idPartition].getConnectedTo().push_back(partitionConnected);
    } 
    //connectado nele mesmo
    if(idPartition == partitionConnected){
        return CONNECTED_TO_SELF;
    }else{
        //partitions[idPartition].getConnectedTo().push_back(partitionConnected);
        return CONNECTED_TO_PARTITION;
    }
    
}

void GPX::joinGraphs(
    graphMap father1, graphMap father2,
    ListOfCities t)
{ // executa a união dos dois grafos, gerando Gu
    for (City c : t.getCitiesList()) {
        // criar a entrada no map da união
        unitedGraph.insert( 
            make_pair(to_string(c.getId()), new CityNode(to_string(c.getId()), c.getX(), c.getY())));

        // colocar as edges no map da união
        for (CityNode::node n : father1[to_string(c.getId())]->getEdges()) {
            unitedGraph[to_string(c.getId())]->addEdge(make_pair(n.first, n.second));
        }
        for (CityNode::node n : father2[to_string(c.getId())]->getEdges()) {
            unitedGraph[to_string(c.getId())]->addEdge(make_pair(n.first, n.second));
        }
    }
}

void GPX::cutCommonEdges()
{ // executa o processo de "cortar" as arestas iguais
    // entre os pais, a partir do grafo da união,
    // gerando o Gu'
    for (graphMap::iterator it = unitedGraph.begin();
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
                            last ); // Deleta a primeira instância do vértice
                        it->second->setAccess(
                            true); // Altera o acesso do vértice (entrada e saída)
                    }
                }
            }
        }
    }
}

vector<string> GPX::findPartition(const string nodeOne)
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

void GPX::findAllPartitions()
{ // irá percorrer todo o grafo
    // encotrando as partições
    // presentes nele
    int id{ 1 };
    vector<vector<string>> partitions;
    vector<string> cities = listOfCitiesWithGhosts;

    while (!cities.empty()) { // enquanto a lista de cidades ainda existir

        partitions.push_back(findPartition(cities.front())); // insere o retorno da função na lista de partições

        /* for (string i : partitions.back()) { // percorre a última partição

            for (int j = 0; j < cities.size(); j++) { // percorre a lista de cidades

                if (i == cities.at(j).getId()) { // se a cidade estiver na última partição

                    cities.erase(cities.begin() + j); // apagar a cidade da lista
                }
            }
        } 

        for(string i : partitions.back()){
            cities.erase(remove(cities.begin(),cities.end(),i),cities.end());
        }
    }

    for (vector<string> vi : partitions) { // retirar partições com tamanho 1
        if (vi.size() != 1) {
            this->partitions.insert(make_pair(id, Partition(id, vi)));
            id++;
        }
    }
}

void GPX::deleteMap(graphMap m)
{ // deletar o mapa completamente,
    // desalocando os ponteiros tb

    for (graphMap::iterator it = m.begin(); it != m.end(); it++) {
        delete it->second;
    }
}

void GPX::checkPartitions()
{
    if (partitions.size() > 1) {

        for (auto& mapIt : unitedGraph) {
        }
    } else {
        partitions.clear();
    }
}

int GPX::whichPartition(const string id)
{ // Procura em qual partição está a cidade procurada, retorna o ID da partição
    for (auto& p : partitions) {
        if (find(p.second.getNodes().begin(), p.second.getNodes().end(), id) != p.second.getNodes().end()) {
            return (p.first);
        }
    }
    return (-1);
} */
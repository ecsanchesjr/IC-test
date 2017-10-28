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

class GPX2 {

    typedef map<string, CityNode*> cityMap;
    //mudar para ponteiro depois
    typedef map<int, Partition> partitionMap;

    enum searchResult { CONNECTED_TO_PARTITION,
        CONNECTED_TO_SELF,
        IS_CONNECTED,
        IS_NOT_CONNECTED };
    enum parent{RED,BLUE};

public:
    //mudar para Tour depois, quando estiver gerando o resultado do crossover
    // Método principal do funcionamento do crossover, recebe dois pais e retorna um Tour filho
    static void crossover(Tour, Tour);

private:
    // Step 1 - Mapear o Tour passado, irá retornar um grafo com as conexões mapeadas
    static cityMap mapToTour(Tour&);

    // Step 2 - Irá criar os nós GHOSTS e inseri-los nos grafos dos pais
    // executar essa ação antes das outras irá "cortar" gasto computacional repetitivo
    static void createGhosts(cityMap&, cityMap&);
    static void insertGhost(string&, cityMap&, CityNode*);

    // Step 3 - Irá gerar o GU (Gráfico da União) dos grafos dos pais
    static void joinGraphs(cityMap&, cityMap&, cityMap&);

    // Step 4 - Irá gerar o GU', o grafo da união dos pais com os cortes executados
    static void cutCommonEdges(cityMap&);

    // Step 5 - Irá encontrar as partições componentes do GU'
    static vector<string> findPartition(const string, cityMap);
    static void findAllPartitions(cityMap, partitionMap&);
    static void cleanInsideAccess(cityMap, partitionMap&);

    // Step 6 - Irá checar se as partições encontradas são recombinantes
    static bool checkPartition(cityMap, cityMap, cityMap&, Partition&);
    static void checkAllPartitions(cityMap, cityMap, cityMap&, partitionMap&);

    // Step 7 - Escolher partições para o filho
    static vector<int> choose(cityMap,cityMap,partitionMap);

    // Utilities
    static double distance(double, double, double, double);
    static void printMap(cityMap&);
    static int whichPartition(const string, partitionMap);
    static void eraseSubVector(vector<string>&, vector<string>&);
    static void deleteMap(cityMap&);
    static vector<string> CityToString(vector<City>);
    static int DFS_inside(string, string, cityMap, Partition, vector<string>&);
    static int DFS_outside(string, cityMap, partitionMap);

    static double parcialDistance(string, string, cityMap, Partition);
};

#endif
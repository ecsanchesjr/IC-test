#include "GPX.hpp"

void GPX::joinGraphs(map<int, CityNode *> father1, map<int, CityNode *> father2, ListOfCities t)
{
    cout << "Entrou na Join" << endl;
    for (City c : t.getCitiesList())
    {
        cout << "Cities " << c.getId() << endl;
        //criar a entrada no map da união
        unitedGraph.insert(make_pair(c.getId(), new CityNode(c.getId(), c.getX(), c.getY())));
        cout << "Insert antes do for" << endl;
        //colocar as edges no map da união
        for (CityNode::node n : father1[c.getId()]->getEdges())
        {
            unitedGraph[c.getId()]->addEdges(make_pair(n.first, n.second));
        }
        for (CityNode::node n : father2[c.getId()]->getEdges())
        {
            unitedGraph[c.getId()]->addEdges(make_pair(n.first, n.second));
        }
        cout << "Passou do for" << endl;
    }
    deleteMap(father1);
    deleteMap(father2);
}

void GPX::cutCommonEdges()
{
    for (map<int, CityNode *>::iterator it = unitedGraph.begin(); it != unitedGraph.end(); it++)
    {
        vector<CityNode::node> &vec = it->second->getEdges();
        for (int i = 0; i < vec.size(); i++)
        {
            int commonEdges{0};
            int last{-1};
            for (int j = 0; j < vec.size(); j++)
            {
                if (vec.at(i).first == vec.at(j).first)
                {
                    commonEdges++;
                    last = j;
                    if (commonEdges > 1)
                    {
                        vec.at(i).second = 0;
                        it->second->deleteEdges(last);
                        it->second->setAccess(true);
                    }
                }
            }
        }
    }
}

vector<int> GPX::findPartition(const int nodeOne){
    CityNode *root = unitedGraph[nodeOne];
    vector<int> idAlreadyVisited;
    deque<int> nextToVisit;

    vector<int> partition;

    bool alreadyVisited{false};
    bool toVisit{false};
    bool cut{false};

    nextToVisit.push_back(root->getId());
    
    while(!nextToVisit.empty()){
      
      	root = unitedGraph[nextToVisit.front()];
        nextToVisit.pop_front();
        
        partition.push_back(root->getId());

        idAlreadyVisited.push_back(root->getId());

        for(CityNode::node n : root->getEdges()){
            
            alreadyVisited = find( idAlreadyVisited.begin(), idAlreadyVisited.end(), n.first) == idAlreadyVisited.end();

            toVisit = find( nextToVisit.begin(), nextToVisit.end(), n.first) == nextToVisit.end();

            cut = n.second != 0;

            if( alreadyVisited && toVisit && cut ){
                nextToVisit.push_back(n.first);
            }
        }
    }
    return(partition);
}


vector<vector<CityNode>> GPX::findPartitions(ListOfCities cities){

    map<int,CityNode*> mapAux = unitedGraph;
    map<int,CityNode*>::iterator it; 
    CityNode *root = mapAux[1];
    deque<int> nextToVisit;
    vector<int> idAlreadyVisited;
    vector<CityNode> aux;
    vector<vector<CityNode>> tmp;

    while(!mapAux.empty()){

        idAlreadyVisited.push_back(root->getId());
        aux.push_back(*root);

        cout << "root->id " << root->getId() << endl;
        for(CityNode::node n : root->getEdges()){

            if( find(idAlreadyVisited.begin(), idAlreadyVisited.end(), n.first) == idAlreadyVisited.end() && find(nextToVisit.begin(), nextToVisit.end(), n.first) == nextToVisit.end() && n.second != 0){
                cout << "first " << n.first << endl;
                nextToVisit.push_back(n.first);
            } 

            if( !nextToVisit.empty() ){
                cout<<"? " << nextToVisit.front() << endl;
                cout << "NTV front " << mapAux[nextToVisit.front()]->getId() << endl;
                root = mapAux[nextToVisit.front()];
                nextToVisit.pop_front();

                aux.push_back(*root);

            }
        }

        tmp.push_back(aux);
        for(CityNode cn : aux){
            cout << "Cn->id " << cn.getId() << endl;
            mapAux.erase(cn.getId());
        }
        cout << "Size " << mapAux.size() << endl;
        aux.clear();
    }

    return(tmp);
} 

void GPX::deleteMap(map<int, CityNode *> m)
{
    for (map<int, CityNode *>::iterator it = m.begin(); it != m.end(); it++)
    {
        delete it->second;
    }
}
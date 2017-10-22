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

vector<vector<CityNode>> GPX::findPartitions(ListOfCities cities)
{
    CityNode *root = unitedGraph[1];
    deque<int> nextToVisit;
    vector<int> idAlreadyVisited;
    vector<CityNode> aux;
    vector<vector<CityNode>> temp;

    //for (int i=0; i<cities.getCitiesList().size(); i++)
    //{
        if(find(aux.begin(), aux.end(), *root) == aux.end()){
            aux.push_back(*root);
            //i++;
        }
        do
        {
            idAlreadyVisited.push_back(root->getId());
            for (CityNode::node p : root->getEdges())
            {
                if (find(idAlreadyVisited.begin(), idAlreadyVisited.end(), p.first) == idAlreadyVisited.end() && find(nextToVisit.begin(), nextToVisit.end(), p.first) == nextToVisit.end() && p.second != 0)
                {
                    nextToVisit.push_back(p.first);
                    cout << "Fisrt " << p.first << endl;
                }
            }
            if (!nextToVisit.empty())
            {
                cout << "Tst " << root->getId() <<endl;
                root = unitedGraph[nextToVisit.front()];
                aux.push_back(*root);
                nextToVisit.pop_front();
                //i++;
            }
        } while (!nextToVisit.empty());
        for(int i : idAlreadyVisited){
            cout << "ID " << i << endl;
        }
        for (map<int, CityNode *>::iterator it = unitedGraph.begin(); it != unitedGraph.end(); it++){
            if(find(idAlreadyVisited.begin(), idAlreadyVisited.end(), it->first) == idAlreadyVisited.end()){
                cout << "TESTE " << endl;
                cout << it->first << endl;
                root = unitedGraph[it->first];
            }
        }
        temp.push_back(aux);
        for (int i : idAlreadyVisited){
            cout << "IdAlready " << i<<endl;
        }
        for(CityNode cn : aux){
            cout << "CityAux " << cn.getId() << endl;
        }
        aux.clear();
    //}
    return (temp);
}

void GPX::deleteMap(map<int, CityNode *> m)
{
    for (map<int, CityNode *>::iterator it = m.begin(); it != m.end(); it++)
    {
        delete it->second;
    }
}
#include "GPX.hpp"

void GPX::joinGraphs(map<int, CityNode *> father1, map<int, CityNode *> father2, ListOfCities t)
{
    for (City c : t.getCitiesList())
    {
        //criar a entrada no map da união
        unitedGraph.insert(make_pair(c.getId(), new CityNode(c.getId(), c.getX(), c.getY())));

        //colocar as edges no map da união
        for (CityNode::node n : father1[c.getId()]->getEdges())
        {
            unitedGraph[c.getId()]->addEdges(make_pair(n.first, n.second));
        }
        for (CityNode::node n : father2[c.getId()]->getEdges())
        {
            unitedGraph[c.getId()]->addEdges(make_pair(n.first, n.second));
        }
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

    for (int i=0; i<cities.getCitiesList().size(); i++)
    {
        if(find(aux.begin(), aux.end(), *root) == aux.end()){
            aux.push_back(*root);
            i++;
        }
        do
        {
            idAlreadyVisited.push_back(root->getId());
            for (CityNode::node p : root->getEdges())
            {
                if (find(idAlreadyVisited.begin(), idAlreadyVisited.end(), p.first) == idAlreadyVisited.end() && find(nextToVisit.begin(), nextToVisit.end(), p.first) == nextToVisit.end() && p.second != 0)
                {
                    nextToVisit.push_back(p.first);
                }
            }
            if (!nextToVisit.empty())
            {
                root = unitedGraph[nextToVisit.front()];
                aux.push_back(*root);
                nextToVisit.pop_front();
                i++;
            }
        } while (!nextToVisit.empty());
        root = unitedGraph[i+1];
        temp.push_back(aux);
        aux.clear();
    }

    return (temp);
}

void GPX::deleteMap(map<int, CityNode *> m)
{
    for (map<int, CityNode *>::iterator it = m.begin(); it != m.end(); it++)
    {
        delete it->second;
    }
}
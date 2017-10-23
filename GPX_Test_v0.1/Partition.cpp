#include "Partition.hpp"

Partition::Partition(){};
Partition::Partition(const int id, vector<int>& nodes):id(id), nodes(nodes){};


vector<int>& Partition::getNodes(){ return(nodes); }
vector<int>& Partition::getConnectedTo(){ return(connectedTo); }
int Partition::getId(){ return(id); }


void Partition::setId(const int id){
    this->id = id;
}

void Partition::setConnectedTo(vector<int>& connectedTo){
    this->connectedTo = connectedTo;
}

void Partition::setNodes(vector<int>& nodes){
    this->nodes = nodes;
}

ostream &operator<<(ostream &output, Partition &partition){
    output << "Partição " << partition.getId() << endl;
    output << "Nós: "; 
    for(int i : partition.getNodes()){
        output << i << " ";
    }
    output << endl;
    output << "Conectadas: ";
    for(int i : partition.getConnectedTo()){
        output << i << " ";
    }
    output << endl;
    return(output);
}
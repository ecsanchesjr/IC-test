#include "Partition.hpp"

Partition::Partition(){};
Partition::Partition(const int id, vector<string>& nodes):id(id), nodes(nodes){};


vector<string>& Partition::getNodes(){ return(nodes); }
/* vector<string>& Partition::getConnectedTo(){ return(connectedTo); } */
int Partition::getId(){ return(id); }


void Partition::setId(const int id){
    this->id = id;
}

/* void Partition::setConnectedTo(vector<string>& connectedTo){
    this->connectedTo = connectedTo;
} */

void Partition::setNodes(vector<string>& nodes){
    this->nodes = nodes;
}

ostream &operator<<(ostream &output, Partition &partition){
    output << "Partition " << partition.getId() << endl;
    output << "Nodes: "; 
    for(string i : partition.getNodes()){
        output << i << " ";
    }
    output << endl;
    /* output << "Connected To: ";
    for(string i : partition.getConnectedTo()){
        output << i << " ";
    } */
    output << endl;
    return(output);
}
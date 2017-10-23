#ifndef PARTITION_H
#define PARTITION_H

#include <vector>
#include <ostream>

using std::vector;
using std::ostream;
using std::endl;

class Partition{
    
    friend ostream &operator<<(ostream&, Partition&);

public:
    Partition();
    Partition(const int, vector<int>&);

    vector<int>& getNodes();
    vector<int>& getConnectedTo();
    int getId();

    void setId(const int);
    void setConnectedTo(vector<int>&);
    void setNodes(vector<int>&);
private:
    int id;
    vector<int> nodes;
    vector<int> connectedTo;
};

#endif
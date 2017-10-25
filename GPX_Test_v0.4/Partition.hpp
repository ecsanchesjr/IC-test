#ifndef PARTITION_H
#define PARTITION_H

#include <vector>
#include <ostream>
#include <string>

using std::string;
using std::vector;
using std::ostream;
using std::endl;

class Partition{
    
    friend ostream &operator<<(ostream&, Partition&);

public:
    Partition();
    Partition(const int, vector<string>&);

    vector<string>& getNodes();
    //vector<string>& getConnectedTo();
    int getId();

    void setId(const int);
    //void setConnectedTo(vector<string>&);
    void setNodes(vector<string>&);
private:
    int id;
    vector<string> nodes;
    //vector<string> connectedTo;
};

#endif
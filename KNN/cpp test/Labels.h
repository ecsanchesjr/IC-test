#ifndef LABELS_H
#define LABELS_H

#include <vector>

using std::vector;

class Labels{

public:
    Labels(){}
    Labels(vector<int> labels):labels(labels){}
    void setLabels(vector<int> labels){
        this->labels = labels;
    }
    vector<int>& getLabels(){
        return(labels);
    }
private:
    vector<int> labels;
};

#endif
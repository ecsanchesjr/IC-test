#ifndef FEATURES_H
#define FEATURES_H

#include <vector>

using std::vector;

class Features{

public:
    Features(){}
    Features(vector<vector<double>> features):features(features){}
    vector<vector<double>>& getFeatures(){
        return(features);
    }
    void setFeatures(vector<vector<double>> features){
        this->features = features; 
    }
private:
    vector<vector<double>> features;
};

#endif
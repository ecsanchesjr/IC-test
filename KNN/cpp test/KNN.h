#ifndef KNN_H
#define KNN_H

#include <cmath>
#include <vector>
#include <utility>
#include <algorithm> 

using std::sort;
using std::vector;
using std::pair;

class KNN{

public:
    void train(const vector<vector<double>>&,const vector<int>&);
    int predict(const vector<double>&,const int=3);
    double test(const vector<vector<double>>&,const vector<int>&,const int=3);
private:
    vector<vector<double>> features;
    vector<int> labels;
    double distance(const int);
    int getKNN(const int);

    static bool myComparator(const pair<double,int>,const pair<double,int>);
};

#endif
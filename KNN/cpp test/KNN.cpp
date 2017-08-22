#include "KNN.h"

void KNN::train(const vector<vector<double>> &features,const vector<int> &labels){
    this->features.resize(features.size());
    for(int i{0};i<features.size();i++){
        for(int j{0};j<features[i].size();j++){
            this->features[i].push_back(features[i][j]);
        }
    }
    for(int label : labels){
        this->labels.push_back(label);
    }
}

int KNN::predict(const vector<double> &feat,const int k){
    int newLabel{-1};
    for(int i{0};i<features.size();i++){
        features[i].push_back(feat[i]);
    }
    newLabel = getKNN(k);
    labels.push_back(newLabel);
    return(newLabel);
}

#include <iostream>
using namespace std;

double KNN::test(const vector<vector<double>> &features,const vector<int> &labels,const int k){
    vector<int> predictions;
    int correct{0};
    for(int i{0};i<features[0].size();i++){
        vector<double> f{features[0][i],features[1][i],features[2][i],features[3][i]};
        predictions.push_back(predict(f,k));
    }
    for(int i{0};i<predictions.size();i++){
        if(predictions[i] == labels[i]){
            correct++;
        }else{
            cout<<"prediction: "<<predictions[i]<<" label: "<<labels[i]<<endl;
        }
    }
    return((double)correct/predictions.size());
}

//distância euclidiana para n dimensões
//sempre pega a última estância adicionada como comparação 
double KNN::distance(const int a){
    double res{0};
    for(vector<double> data : features){
        res+=pow((data[a]-data[data.size()-1]),2);
    }
    res=sqrt(res);
}

int KNN::getKNN(const int k){
    vector<pair<double,int>> nn;
    int l0{0},l1{0},l2{0};
    for(int i{0};i<features[0].size()-1;i++){
        pair<double,int> p{distance(i),labels[i]};
        nn.push_back(p);
    }
    sort(nn.begin(),nn.end(),myComparator);
    for(int i{0};i<k;i++){
        switch(nn[i].second){
            case 0:{
                l0++;
                break;
            }
            case 1:{
                l1++;
                break;
            }
            case 2:{
                l2++;
                break;
            }
        }
    }
    if(l0>l1 && l0>l2){
        return(0);
    }else if(l1>l0 && l1>l2){
        return(1);
    }else{
        return(2);
    }
}

bool KNN::myComparator(const pair<double,int> a,const pair<double,int> b){
    return(a.first < b.first);
}


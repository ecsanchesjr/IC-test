#include <iostream>
#include <vector>
#include "ImportData.h"
#include "Features.h"
#include "Labels.h"
#include "KNN.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;



int main(){
    ImportData trainData,testData;
    KNN classifier;
    
    trainData.read("iris_train.data");
    classifier.train(trainData.getFeaturesData().getFeatures(),trainData.getLabelData().getLabels());


    testData.read("iris_test.data");

    cout<<"acertos: "<<classifier.test(testData.getFeaturesData().getFeatures(),testData.getLabelData().getLabels(),10)<<endl;

/* 
    double f1{0},f2{0},f3{0},f4{0};
    int k{0};

    while(cin){
        cout<<"Digite os dados da flor a classificar: ";
        cin>>f1>>f2>>f3>>f4;
        cout<<"Digite o k desejado: ";
        cin>>k;
        
        vector<double> feat{f1,f2,f3,f4};

        int ret = classifier.predict(feat,k);

        switch(ret){
            case 0:{
                cout<<"Iris-setosa"<<endl;
                break;
            }
            case 1:{
                cout<<"Iris-versicolor"<<endl;
                break;
            }
            case 2:{
                cout<<"Iris-virginica"<<endl;
                break;
            }
        }
    } */

    return(0);
}
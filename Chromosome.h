#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cstdlib>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

template <class type> 
class Chromosome{

public:
    Chromosome();

    void setData(vector<type>);
    void setFitness(double);
    void setNext(Chromosome*);
    void printData();

    vector<type>& getData();
    double getFitness() const;
    Chromosome* getNext() const;
private:    
    vector<type> data;
    double fitness;
    Chromosome *next;
};

template <class type>
Chromosome<type>::Chromosome(){}

template <class type>
void Chromosome<type>::setData(vector<type> d){
    data = d;
}

template <class type>
void Chromosome<type>::setFitness(double fit){
    fitness = fit;
}

template <class type>
void Chromosome<type>::setNext(Chromosome<type> *n){
    next = n;
}

//debug
template <class type>
void Chromosome<type>::printData(){
    for(int i=0;i<data.size();i++){
        cout<<data[i];
    }
    cout<<endl;
}

template <class type>
vector<type>& Chromosome<type>::getData(){
    return(data);
}

template <class type>
double Chromosome<type>::getFitness() const{
    return(fitness);
}

template <class type>
Chromosome<type>* Chromosome<type>::getNext() const{
    return(next);
}

#endif
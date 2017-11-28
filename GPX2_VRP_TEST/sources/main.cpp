#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "ImportData.hpp"
#include "AuxReader.hpp"
#include "City.hpp"
#include "Tour.hpp"
#include "Population.hpp"

using namespace std;
int calcTotalFittness(vector<Population> pops){
    int best=0;
    for(auto pop:pops){
        best+=pop.bestFitness();
    }
    return best;
}

int main(){
    const int popSize=10;
    const int maxGenerations=15;
   ImportData inFile("Projeto-Auxiliar/fruitybun250.vrp");
  // inFile.printInfos();
   //Lista de Customer tranformadas em city para uso no GPX
   vector<Customer> customerList = inFile.getCustomerList();
   vector<City> convertedList;
   vector<Tour> Tours;
   vector<Population> pops;
   for(auto cu : customerList){
       convertedList.push_back(City(cu.getId(),cu.getX(),cu.getY()));
   }
   /*for(auto cu : convertedList){
       cout <<cu <<endl;
   }*/
   //Mapeamento de Rotas a partir do projeto .py
   AuxReader ar("Projeto-Auxiliar/phase2.txt");
   vector<vector<int>> routeList = ar.getRoutes();
   //ar.printRoutes();
   for(auto route: routeList){
       vector<City> temp;
       for(auto id: route){ 
            temp.push_back(convertedList[id-1]);
       }
       Tours.push_back(Tour(temp));
       temp.clear();
   }
   //Carregando uma população individual para cada rota
   for(auto tour: Tours){
       Population temp;
       temp.addNewTour(tour);
       for (unsigned int i=0; i<((popSize -1));i++){
        Tour ttemp=tour;
        ttemp.shuffleRoute();
        temp.addNewTour(ttemp);
    }
    pops.push_back(temp);
   }
   //Debugando as populações geradass
   for (auto pop: pops){
       cout<<pop<<endl;
   }
   cout<<"Melhor Fitness: "<<calcTotalFittness(pops)<<endl;

}

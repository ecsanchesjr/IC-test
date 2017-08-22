#include "ImportData.h"

void ImportData::read(string name){
    ifstream file;
    file.open(name);
    string word{""};
    vector<string> result;

    featureData.getFeatures().resize(4);

    if(file.is_open()){
        while(file>>word){
            result = explode(word,',');
            for(int i=0;i<result.size()-1;i++){
                featureData.getFeatures()[i].push_back(stod(result[i]));
            }
            if(result[result.size()-1].compare("Iris-setosa")==0){
                labelData.getLabels().push_back(0);
            }else if(result[result.size()-1].compare("Iris-versicolor")==0){
                labelData.getLabels().push_back(1);
            }else{
                labelData.getLabels().push_back(2);
            }
        }
    }
}

vector<string> ImportData::explode(string &word,char c){
    vector<string> res;
    istringstream iss(word);

    for(string s ; getline(iss,s,c);){
        res.push_back(s);
    }
    return(res);
}

Labels ImportData::getLabelData() const{
    return(labelData);
}

Features ImportData::getFeaturesData() const{
    return(featureData);
}

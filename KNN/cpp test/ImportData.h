#ifndef IMPORTDATA_H
#define IMPORTDATA_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Labels.h"
#include "Features.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::getline;
using std::istringstream;
using std::stod;

class ImportData{

public:
    void read(string);
    Labels getLabelData() const;
    Features getFeaturesData() const;
private:
    Labels labelData;
    Features featureData;
    vector<string> explode(string&,char);
};

#endif
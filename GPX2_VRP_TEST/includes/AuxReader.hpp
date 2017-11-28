#ifndef AUXREADER_H
#define AUXREADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;
class AuxReader
{
  public:
    AuxReader(string);
    vector<vector<int>> getRoutes();
    void printRoutes();

  private:
    ifstream popInicialFile;
    vector<vector<int>> routes;
    vector<string> explode(string del, string str);
};

#endif
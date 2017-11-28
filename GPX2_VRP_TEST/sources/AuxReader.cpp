#include  "AuxReader.hpp"

AuxReader:: AuxReader(string filename){
    int ignorelines=0;
    cout<<"Importando Arquivo"<<endl;
    popInicialFile.open(filename);
    string line;
    string newfile;
    vector<int> tempaux;
    while(getline(popInicialFile,line)){
        if(ignorelines<4){            
        }else{
            vector<string> temp= explode("->",line);
            //cout <<"Rota " <<ignorelines -3 <<":";
            for(auto it : temp)
            {
               // cout<< it <<" ";
                tempaux.push_back(stoi(it));
            }
            routes.push_back(tempaux);
           //cout <<endl;
           tempaux.clear();
        }
        ignorelines++;
    }
    //printRoutes();
}
void AuxReader::printRoutes(){
    int rN=1;
    for(auto it : routes)
    {
        cout<< "Rota "<<rN << ":" ;
        for(auto it2: it){
            cout<<it2<< " ";
        }
        rN++;
        cout<<endl;
    }
}

vector<vector<int>> AuxReader::getRoutes(){
    return routes;
}

vector<string> AuxReader::explode(string del, string str)
{
  int slen = str.length();
  int dlen = del.length();
  int found_a;
  string before;
  vector<string> final;
  vector<string> fail (0);
  if(dlen == 0) return fail;
  if(slen == 0) return fail;
  for(int counter = 0; counter < slen; counter ++)
  {
    found_a = str.find(del);
    if(found_a != string::npos)
    {
      before = str.substr(0, found_a + dlen);
      before.erase(remove(before.begin(),before.end(),'>'),before.end());
      before.erase(remove(before.begin(),before.end(),'-'),before.end());
      final.push_back(before);
      str.replace(0, found_a + dlen, "");
    }
    else
    {
      if(str.length() > 0)
      {
        str.erase(remove(str.begin(),str.end(),'>'),str.end());
        str.erase(remove(str.begin(),str.end(),'-'),str.end());
        final.push_back(str);
        str.replace(0, str.length(), "");
      }
      else
      {
        break;
      }
    }
  }
  return final;
}
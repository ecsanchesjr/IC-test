#include "ImportData.h"

ImportData::ImportData(string nome)
{
    string input;
    cout << "Importando Arquivo \n";
    myfile.open(nome);
    myfile >> input;
    regexManager(input);
    while (myfile >> input)
    {
        regexManager(input);
        if (findIgnoredWords(input))
        {
            reader(flag, input);
        }
    }
}

void ImportData::regexManager(string input)
{
    regex integer("(\\+|-)?[[:digit:]]+");

    regex name("NAME(.*)");
    regex type("TYPE(.*)");
    regex comment("COMMENT(.*)");
    regex dimension("DIMENSION(.*)");
    regex edge_type("EDGE(.*)");
    regex node_comment("NODE(.*)");
    if (regex_match(input, name))
    {
        flag = "name";
        //cout << "Nome\n";
    }
    else if (regex_match(input, type))
    {
        flag = "type";
        //cout << "Tipo\n";
    }
    else if (regex_match(input, comment))
    {
        flag = "comment";
    }
    else if (regex_match(input, dimension))
    {
        flag = "dimension";
    }
    else if (regex_match(input, edge_type))
    {
        flag = "edge_type";
    }
    else if (regex_match(input, node_comment))
    {
        flag = "node_comment";
    }
    else if (regex_match(input, integer) && flagaux == "wait for number")
    {
        flag = "integer";
    }
}

bool ImportData::findIgnoredWords(string input)
{
    regex ignore(":|NAME(.*)|TYPE(.*)|COMMENT(.*)|DIMENSION(.*)|EDGE(.*)|EOF");
    if (regex_match(input, ignore))
    {
        return false;
    }
    //  cout << input;
    return true;
}

void ImportData::reader(string flag, string input)
{
    if (flag == "name")
    {
        //cout << input << " is a name! \n";
    }
    else if (flag == "type")
    {
        //cout << input << " is a type! \n";
    }
    else if (flag == "comment")
    {
        //cout << input << " is a comment! \n";
    }
    else if (flag == "dimension")
    {
        //cout << input << " is a dimension! \n";
        citiescoord.reserve(std::stoi(input));
        flagaux = "wait for number";
    }
    else if (flag == "edge_type")
    {
        //cout << input << " is an edge_type! \n";
    }
    else if (flag == "node_comment")
    {
        //cout << input << " is an node_comment! \n";
    }
    else if (flag == "integer" && flagaux == "wait for number")
    {
        //  cout << "I: " << input;
        myfile >> input;
        int x = std::stoi(input);
        //   cout << "\t X: " << input;
        myfile >> input;
        int y = std::stoi(input);
        //     cout << "\t Y: " << input << "\n";
        citiescoord.push_back(City(x,y));
    }
}

vector<City> ImportData::getCitiesCoord(){
    return citiescoord;
}
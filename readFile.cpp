// reading a text file
#include "readFile.hpp"
using namespace std;

vector<string> stringVectorFromFile(string fileName)
{

    vector<string> newVec;
    string line;
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            newVec.push_back(line);
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";

    return newVec;
}

vector<int> intVectorFromFile(string fileName)
{
    vector<int> newVec;
    string line;
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            newVec.push_back(stoi(line));
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";

    return newVec;
}
#include "readFile.hpp"
#include <vector>
#include <map>
#include <regex>

using namespace std;

void holdsShinyGoldBag(map<string, map<string, int>> &bagMap, string &bag, int &indicator)
{

    cout << "In function with " << bag << endl;

    if (bag == "shiny gold")
    {
        cout << "Bag found" << endl;
        indicator = 1;
        return;
    }

    map<string, int>::iterator cursor;
    map<string, int> bagContents = bagMap[bag];
    for (cursor = bagContents.begin(); cursor != bagContents.end(); ++cursor)
    {
        string nextBag = cursor->first;
        cout << "Next Bag: " << nextBag << endl;
        return holdsShinyGoldBag(bagMap, nextBag, indicator);
    }
    cout << "Terminating chain with " << bag << endl;
}

int main()
{
    vector<string> myVec = stringVectorFromFile("problem7inputs.txt");

    map<string, map<string, int>> bagMap = {};

    regex bagName("^(\\w+\\s\\w+)\\sbags?\\scontain", regex::ECMAScript);
    regex containingBags("(\\d)(\\s\\w+\\s\\w+)*", regex::ECMAScript);

    //First, construct the bagMap
    for (int i = 0; i < myVec.size(); i++)
    {
        string line = myVec[i];
        smatch sm;
        //get bagName
        regex_search(line, sm, bagName);
        string key = sm[1].str();

        sregex_iterator findBags(line.begin(), line.end(), containingBags);
        sregex_iterator end;

        map<string, int> containingBagMap = {};
        while (findBags != end)
        {
            smatch match = *findBags;
            int quantity = match.str()[0] - '0';
            string key = match.str().substr(2, string::npos);
            //cout << "Key: " << key << " Quantity: " << quantity << endl;
            containingBagMap.insert(pair<string, int>(key, quantity));
            findBags++;
        }
        bagMap.insert(pair<string, map<string, int>>(key, containingBagMap));
    }

    int bagCount = 0;
    //Go through all bags, if they can hold a 'shiny gold' bag count them
    map<string, map<string, int>>::iterator cursor;
    for (cursor = bagMap.begin(); cursor != bagMap.end(); cursor++)
    {
        string thisBag = cursor->first;
        int indicator = 0;
        cout << "Going in first level with " << thisBag << endl;
        holdsShinyGoldBag(bagMap, thisBag, indicator);
        if (indicator == 1)
        {
            bagCount++;
        }
    }

    cout << "Bagcount: " << bagCount << endl;
}
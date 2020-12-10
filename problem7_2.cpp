#include "readFile.hpp"
#include <vector>
#include <map>
#include <regex>

using namespace std;

void holdsShinyGoldBag(map<string, map<string, int>> &bagMap, string &bag, int &counter)
{

    cout << "In function with " << bag << endl;

    map<string, int>::iterator cursor;
    map<string, int> bagContents = bagMap[bag];

    for (cursor = bagContents.begin(); cursor != bagContents.end(); ++cursor)
    {
        string nextBag = cursor->first;
        int nextBagCount = cursor->second;
        cout << "Adding " << nextBagCount << " from " << nextBag << endl;
        counter += nextBagCount;
        int currentTotal = counter;
        if (!bagMap[nextBag].empty())
        {
            holdsShinyGoldBag(bagMap, nextBag, counter);
            cout << "Back from " << nextBag << " Added " << (counter - currentTotal) << endl;
            //Add (counter-currentTotal) * (nextCount - 1)
            counter += (counter - currentTotal) * (nextBagCount - 1);
        }
        else
        {
            cout << "Empty bag" << endl;
        }
    }
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

    string thisBag = "shiny gold";
    int count = 0;

    holdsShinyGoldBag(bagMap, thisBag, count);

    cout << "Bagcount: " << count << endl;
}
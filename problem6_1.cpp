#include "readFile.hpp"
#include <vector>
#include <set>

using namespace std;

int main()
{
    vector<string> myVec = stringVectorFromFile("problem6inputs.txt");

    set<char> yesAnswers = {};
    int count = 0;
    for (int i = 0; i < myVec.size(); i++)
    {
        string line = myVec[i];
        if (line.empty())
        {
            count += yesAnswers.size();
            yesAnswers = {};
            continue;
        }
        for (int j = 0; j < line.length(); j++)
        {
            yesAnswers.insert(line[j]);
        }
    }

    cout << "There were " << count << " yes answers." << endl;
}
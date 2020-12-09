#include "readFile.hpp"
#include <vector>
#include <set>

using namespace std;

int main()
{
    vector<string> myVec = stringVectorFromFile("problem6inputs.txt");

    vector<string> lines = {};
    int count = 0;
    for (int i = 0; i < myVec.size(); i++)
    {
        string line = myVec[i];
        if (line.empty())
        {
            set<char> common = {};
            for (int j = 0; j < lines.size(); j++)
            {
                string currentLine = lines[j];
                if (j == 0)
                {
                    for (int k = 0; k < currentLine.length(); k++)
                    {
                        common.insert(currentLine[k]);
                    }
                }
                else
                {
                    set<char>::iterator it = common.begin();
                    while (it != common.end())
                    {
                        if (currentLine.find(*it) == string::npos)
                        {
                            it = common.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }
                }
            }

            lines = {};
            count += common.size();
            continue;
        }

        lines.push_back(line);
    }

    cout << "There were " << count << " yes answers." << endl;
}
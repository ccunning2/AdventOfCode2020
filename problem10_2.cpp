#include "readFile.hpp"
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

long long int countWays(vector<int> &vec, int pos, map<int, long long int> &counts)
{
    //We made it to the end, this is a valid way
    if (pos == vec.size() - 1)
    {
        return 1;
    }

    //Get eligible indexes
    vector<int> candidateIndexes = {};
    for (int i = 0; i < 3; i++)
    {
        int index = pos + i + 1;
        if (index < vec.size() && (vec[index] - vec[pos]) <= 3)
        {
            candidateIndexes.push_back(index);
        }
    }

    long long int total = 0;
    for (auto index : candidateIndexes)
    {
        long long int indexCount = 0;
        if (counts.find(index) != counts.end())
        {
            indexCount = counts[index];
        }
        else
        {
            indexCount = countWays(vec, index, counts);
            counts[index] = indexCount;
        }
        total += indexCount;
    }

    return total;
}

int main()
{
    vector<int> myVec = intVectorFromFile("problem10input.txt");

    sort(myVec.begin(), myVec.end());
    myVec.insert(myVec.begin(), 0);

    map<int, long long int> solutionMap = {};

    long long int total = countWays(myVec, 0, solutionMap);
    cout << "Total: " << total << endl;
}
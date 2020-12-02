#include "readFile.hpp"
#include <vector>

using namespace std;

int main()
{
    vector<int> myVec = intVectorFromFile("problem1inputs.txt");

    const int desiredSum = 2020;
    int candidate1, candidate2, candidate3;
    for (int i = 0; i < myVec.size(); i++)
    {
        candidate1 = myVec[i];
        for (int j = 0; j < myVec.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            candidate2 = myVec[j];

            //This was part 1, part 2 is below
            // if ((candidate1 + candidate2) == desiredSum)
            // {
            //     cout << "The value you are looking for is " << candidate1 * candidate2 << "\n";
            //     return 0;
            // }
            for (int k = 0; k < myVec.size(); k++)
            {
                if (k == j)
                {
                    continue;
                }
                candidate3 = myVec[k];
                if ((candidate1 + candidate2 + candidate3) == desiredSum)
                {
                    cout << "The value you are looking for is " << candidate1 * candidate2 * candidate3 << "\n";
                    return 0;
                }
            }
        }
    }
}
#include "readFile.hpp"
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> myVec = intVectorFromFile("problem10input.txt");

    sort(myVec.begin(), myVec.end());

    int differenceOfOneCount = 0, differenceOfThreeCount = 0;

    for (int i = 0; i < myVec.size(); i++)
    {
        int last;
        last = (i > 0) ? myVec[i - 1] : 0;
        int current = myVec[i];
        int difference = current - last;
        if (difference == 1)
        {
            differenceOfOneCount++;
        }

        if (difference == 3)
        {
            differenceOfThreeCount++;
        }
    }

    //Always add one more diff of 3
    differenceOfThreeCount++;

    cout << "Diff fo 1: " << differenceOfOneCount << " Diff of 3: " << differenceOfThreeCount << endl;
    int answer = differenceOfOneCount * differenceOfThreeCount;
    cout << "Answer: " << answer << endl;
}
#include "readFile.hpp"
#include <vector>

using namespace std;

int main()
{

    vector<long long int> myVec = lliVectorFromFile("problem9inputs.txt");

    long long int desiredSum = 1212510616;

    for (int i = 0; i < myVec.size(); i++)
    {
        long long int runningSum = 0;
        long long int smallestinRange = myVec[i];
        long long int largestInRange = myVec[i];

        for (int j = i; j < myVec.size(); j++)
        {
            if (myVec[j] < smallestinRange)
            {
                smallestinRange = myVec[j];
            }

            if (myVec[j] > largestInRange)
            {
                largestInRange = myVec[j];
            }

            runningSum += myVec[j];
            if (runningSum > desiredSum)
            {
                break;
            }
            if (runningSum == desiredSum)
            {
                cout << "Found the desired sum. i = " << i << " j = " << j << endl;
                cout << "Smallest in range: " << smallestinRange << endl;
                cout << "Largest in range: " << largestInRange << endl;
                long long int newTotal = smallestinRange + largestInRange;
                cout << "Encryption Weakness: " << newTotal << endl;
                return 0;
            }
        }
    }
}
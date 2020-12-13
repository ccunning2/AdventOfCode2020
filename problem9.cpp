#include "readFile.hpp"
#include <vector>
#include <valarray>

using namespace std;

const int PREAMBLE_LENGTH = 25;

bool isValidNumber(const vector<long long int> numberSelection, long long int candidate, int minRange)
{
    const int maxRange = minRange + PREAMBLE_LENGTH - 1;
    //Go through numberselection. If there are two numbers whose sum is equal to candidate, return true.
    for (int i = minRange; i <= maxRange; i++)
    {

        const long long int number1 = numberSelection[i];
        for (int k = minRange; k <= maxRange; k++)
        {
            if (k == i)
            {
                continue;
            }
            const long long int number2 = numberSelection[k];
            if ((number1 + number2) == candidate)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{

    vector<long long int> myVec = lliVectorFromFile("problem9inputs.txt");

    for (int i = 0; i < myVec.size(); i++)
    {
        int candidateIndex = PREAMBLE_LENGTH + i;
        long long int candidate = myVec[candidateIndex];
        if (!isValidNumber(myVec, candidate, i))
        {
            cout << "The invalid number is " << candidate << endl;
            break;
        }
    }
}
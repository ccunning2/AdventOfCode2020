#include "readFile.hpp"
#include <vector>

using namespace std;

int main()
{
    vector<int> myVec = intVectorFromFile("problem1inputs.txt");

    for (vector<int>::iterator it = myVec.begin(); it != myVec.end(); it++)
    {
        cout << *it << '\n';
    }
}
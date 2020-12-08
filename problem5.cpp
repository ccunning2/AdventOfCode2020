#include "readFile.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int findVal(int min, int max, string directions)
{
    if (max - min == 0)
    {
        return max;
    }

    float midpoint = (max - min) / 2.0f;

    if (directions[0] == 'F' || directions[0] == 'L')
    {
        max -= (floor(midpoint) + 1);
    }

    if (directions[0] == 'B' || directions[0] == 'R')
    {
        min += ceil(midpoint);
    }
    return findVal(min, max, directions.substr(1, directions.npos));
}

int main()
{
    vector<string> myVec = stringVectorFromFile("problem5inputs.txt");

    int maxId = 0;
    vector<int> seatIds;

    for (int i = 0; i < myVec.size(); i++)
    {
        string seatCode = myVec[i];
        string rows = seatCode.substr(0, 7);
        string cols = seatCode.substr(7, seatCode.npos);
        int row = findVal(0, 127, rows);
        int col = findVal(0, 7, cols);
        int seatId = row * 8 + col;
        seatIds.push_back(seatId);
        if (seatId > maxId)
        {
            maxId = seatId;
        }
    }

    sort(seatIds.begin(), seatIds.end());

    cout << "The max ID is: " << maxId << endl;

    int yourSeatId = 0;
    int offset = seatIds[0];
    for (int i = 0; i < seatIds.size(); i++)
    {
        if ((offset + i) != seatIds[i])
        {
            yourSeatId = seatIds[i - 1] + 1;
            cout << "Your seat ID is: " << yourSeatId << endl;
            break;
        }
    }
}
#include "readFile.hpp"
#include <vector>
#include <algorithm>

using namespace std;

void printBoard(vector<string> &vec)
{
    for (auto line : vec)
    {
        cout << line << endl;
    }
    cout << endl;
    cout << "----------------";
    cout << endl;
}

int countOccupiedSeats(vector<string> &room)
{
    int occupiedCount = 0;
    for (int i = 0; i < room.size(); i++)
    {
        string row = room[i];
        for (int k = 0; k < row.length(); k++)
        {
            if (row[k] == '#')
            {
                occupiedCount++;
            }
        }
    }
    return occupiedCount;
}

int checkChar(char c)
{
    if (c == '#')
    {
        return 1;
    }
    return 0;
}

int checkAdjacency(vector<string> &seats, int row, int col)
{
    bool checkRowAbove = row != 0;
    bool checkRowBelow = row != seats.size() - 1;
    bool checkPrevCol = col != 0;
    bool checkNextCol = col != seats[0].length() - 1;

    int adjacentSeatCount = 0;

    if (checkRowAbove)
    {
        string rowAbove = seats[row - 1];
        if (checkPrevCol)
        {
            char upperLeft = rowAbove[col - 1];
            adjacentSeatCount += checkChar(upperLeft);
        }
        char upper = rowAbove[col];
        adjacentSeatCount += checkChar(upper);
        if (checkNextCol)
        {
            char upperRight = rowAbove[col + 1];
            adjacentSeatCount += checkChar(upperRight);
        }
    }

    if (checkRowBelow)
    {
        string rowBelow = seats[row + 1];
        if (checkPrevCol)
        {
            char lowerLeft = rowBelow[col - 1];
            adjacentSeatCount += checkChar(lowerLeft);
        }
        char lower = rowBelow[col];
        adjacentSeatCount += checkChar(lower);
        if (checkNextCol)
        {
            char lowerRight = rowBelow[col + 1];
            adjacentSeatCount += checkChar(lowerRight);
        }
    }

    string currentRow = seats[row];
    if (checkPrevCol)
    {
        char left = currentRow[col - 1];
        adjacentSeatCount += checkChar(left);
    }

    if (checkNextCol)
    {
        char right = currentRow[col + 1];
        adjacentSeatCount += checkChar(right);
    }

    return adjacentSeatCount;
}

int main()
{
    vector<string> myVec = stringVectorFromFile("problem11input.txt");

    bool change = false;
    int interationCount = 0;
    do
    {
        vector<string> nextRound = {};
        change = false;
        for (int i = 0; i < myVec.size(); i++)
        {
            string row = myVec[i];
            for (int j = 0; j < row.length(); j++)
            {
                int adjacencyCount = checkAdjacency(myVec, i, j);
                char seat = row.at(j);
                if (seat == 'L' && adjacencyCount == 0)
                {
                    //It becomes occupied
                    row[j] = '#';
                    change = true;
                }
                if (seat == '#' && adjacencyCount >= 4)
                {
                    row[j] = 'L';
                    change = true;
                }
            }
            nextRound.push_back(row);
        }
        myVec.assign(nextRound.begin(), nextRound.end());
        interationCount++;
        printBoard(myVec);
    } while (change);

    int occupiedSeats = countOccupiedSeats(myVec);

    cout << "Occupied Seats: " << occupiedSeats << endl;
    cout << "Iterations: " << interationCount << endl;
}
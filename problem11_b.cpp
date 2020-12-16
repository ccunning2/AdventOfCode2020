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

int checkAboveAndLeft(vector<string> &seats, int row, int col)
{
    if (row == 0 || col == 0)
    {
        return 0;
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    {
        char seat = seats[i].at(j);
        if (seat == 'L')
        {
            return 0;
        }
        if (seat == '#')
        {
            return 1;
        }
    }
    return 0;
}

int checkLeft(vector<string> &seats, int row, int col)
{
    if (col == 0)
    {
        return 0;
    }

    string currRow = seats[row];
    for (int i = col - 1; i >= 0; --i)
    {
        if (currRow.at(i) == 'L')
        {
            return 0;
        }
        if (currRow.at(i) == '#')
        {
            return 1;
        }
    }
    return 0;
}

int checkDownAndLeft(vector<string> &seats, int row, int col)
{
    int maxrow = seats.size() - 1;
    for (int i = row + 1, j = col - 1; i <= maxrow && j >= 0; i++, j--)
    {
        char seat = seats[i].at(j);

        if (seat == 'L')
        {
            return 0;
        }
        if (seat == '#')
        {
            return 1;
        }
    }
    return 0;
}

int checkAbove(vector<string> &seats, int row, int col)
{
    row--;
    while (row >= 0)
    {
        char seat = seats[row][col];
        if (seat == 'L')
        {
            return 0;
        }
        if (seat == '#')
        {
            return 1;
        }
        row--;
    }
    return 0;
}

int checkBelow(vector<string> &seats, int row, int col)
{
    row++;
    while (row <= seats.size() - 1)
    {
        char seat = seats[row][col];
        if (seat == 'L')
        {
            return 0;
        }
        if (seat == '#')
        {
            return 1;
        }
        row++;
    }
    return 0;
}

int checkRight(vector<string> &seats, int row, int col)
{
    int maxcol = seats[0].length() - 1;
    if (col == maxcol)
    {
        return 0;
    }

    string currRow = seats[row];
    for (int i = col + 1; i <= maxcol; i++)
    {
        if (currRow.at(i) == 'L')
        {
            return 0;
        }
        if (currRow.at(i) == '#')
        {
            return 1;
        }
    }
    return 0;
}

int checkDownAndRight(vector<string> &seats, int row, int col)
{
    int maxrow = seats.size() - 1;
    int maxcol = seats[0].length() - 1;

    for (int i = row + 1, j = col + 1; i <= maxrow && j <= maxcol; i++, j++)
    {
        char seat = seats[i].at(j);
        ;
        if (seat == 'L')
        {
            return 0;
        }
        if (seat == '#')
        {
            return 1;
        }
    }
    return 0;
}

int checkAboveAndRight(vector<string> &seats, int row, int col)
{

    int maxcol = seats[0].length() - 1;

    if (row == 0 || col == maxcol)
    {
        return 0;
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j <= maxcol; i--, j++)
    {
        char seat = seats[i].at(j);
        if (seat == 'L')
        {
            return 0;
        }
        if (seat == '#')
        {
            return 1;
        }
    }
    return 0;
}

int checkVisibleOccupiedSeats(vector<string> &seats, int row, int col)
{

    int occupiedSeatCount = 0;

    occupiedSeatCount += checkAboveAndLeft(seats, row, col);
    occupiedSeatCount += checkLeft(seats, row, col);
    occupiedSeatCount += checkDownAndLeft(seats, row, col);
    occupiedSeatCount += checkBelow(seats, row, col);
    occupiedSeatCount += checkDownAndRight(seats, row, col);
    occupiedSeatCount += checkRight(seats, row, col);
    occupiedSeatCount += checkAboveAndRight(seats, row, col);
    occupiedSeatCount += checkAbove(seats, row, col);

    return occupiedSeatCount;
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
                int adjacencyCount = checkVisibleOccupiedSeats(myVec, i, j);
                char seat = row.at(j);
                if (seat == 'L' && adjacencyCount == 0)
                {
                    //It becomes occupied
                    row[j] = '#';
                    change = true;
                }
                if (seat == '#' && adjacencyCount >= 5)
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
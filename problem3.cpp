#include "readFile.hpp"
#include <vector>
#include <tuple>

//Below were used in part 1
#define PART1_RIGHT 3
#define PART1_DOWN 1

using namespace std;

int main()
{
    vector<string> myVec = stringVectorFromFile("problem3input.txt");

    vector<tuple<int, int>> slopes;

    vector<int> answers;

    slopes.push_back(make_tuple(1, 1));
    slopes.push_back(make_tuple(3, 1));
    slopes.push_back(make_tuple(5, 1));
    slopes.push_back(make_tuple(7, 1));
    slopes.push_back(make_tuple(1, 2));

    for (int j = 0; j < slopes.size(); j++)
    {
        int xPos = 0, treeCount = 0;
        int rightSlope = get<0>(slopes[j]);
        int downSlope = get<1>(slopes[j]);

        for (int i = downSlope; i < myVec.size(); i += downSlope)
        {
            string current = myVec[i];
            xPos += rightSlope;
            int stringLength = current.length();
            while (xPos >= stringLength)
            {
                current += current;
                stringLength = current.length();
            }

            if (current.at(xPos) == '#')
            {
                treeCount++;
            }
        }
        answers.push_back(treeCount);
    }

    int finalAnswer = 1;
    for (int k = 0; k < answers.size(); k++)
    {
        finalAnswer *= answers[k];
    }

    cout << "Answer is " << finalAnswer << "\n";
}
#include "readFile.hpp"
#include <vector>
#include <regex>
#include <sys/types.h>

#define MIN_RANGE_PLACE 1
#define MAX_RANGE_PLACE 2
#define LETTER_PLACE 3
#define STRING_PLACE 4

using namespace std;

bool isPasswordValidPartOne(int min, int max, string required, string password)
{
    regex e(required, regex_constants::ECMAScript);

    ptrdiff_t const match_count(distance(
        sregex_iterator(password.begin(), password.end(), e),
        sregex_iterator()));

    return (match_count >= min) && (match_count <= max);
}

bool isPasswordValidPartTwo(int posOne, int posTwo, string required, string password)
{
    char chArray[password.size() + 1];
    char requiredChar = required.c_str()[0];
    password.copy(chArray, password.size() + 1);
    posOne -= 1;
    posTwo -= 1;
    return ((chArray[posOne] == requiredChar) != (chArray[posTwo] == requiredChar));
}

int main()
{

    vector<string> myVec = stringVectorFromFile("problem2inputs.txt");

    regex e("^(\\d+)-(\\d+) ([a-z]): ([a-z]+){1}", regex_constants::ECMAScript);

    int validPasswords = 0;
    for (int i = 0; i < myVec.size(); i++)
    {
        string line = myVec[i];
        smatch cm;
        bool match = regex_search(line, cm, e);

        int minRange = stoi(cm[MIN_RANGE_PLACE].str());
        int maxRange = stoi(cm[MAX_RANGE_PLACE].str());
        string letter = cm[LETTER_PLACE].str();
        string stringToCheck = cm[STRING_PLACE].str();
        if (isPasswordValidPartTwo(minRange, maxRange, letter, stringToCheck))
        {
            validPasswords++;
        }
    }
    cout << "The number of valid passwords is: " << validPasswords << "\n";
}

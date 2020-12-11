#include "readFile.hpp"
#include <vector>
#include <set>

using namespace std;

void runProgram(vector<string> &program)
{

    set<string> ranCommands;

    int accumulator = 0, instruction = 0;
    bool programEnded = false;
    while (!programEnded)
    {
        string line = program[instruction];

        if (ranCommands.find(line + to_string(instruction)) != ranCommands.end())
        {
            cout << "Value prior to running second time: " << accumulator << endl;
            programEnded = true;
            break;
        }
        ranCommands.insert(line + to_string(instruction));
        string command = line.substr(0, 3);
        char sign = line[4];
        int value = stoi(line.substr(5, string::npos));
        if (command == "acc")
        {
            if (sign == '+')
            {
                accumulator += value;
            }
            else if (sign == '-')
            {
                accumulator -= value;
            }
            instruction++;
        }
        else if (command == "jmp")
        {
            if (sign == '+')
            {
                instruction += value;
            }
            else if (sign == '-')
            {
                instruction -= value;
            }
        }
        else if (command == "nop")
        {
            instruction++;
        }
    }
}

int main()
{
    vector<string> myVec = stringVectorFromFile("problem8inputs.txt");

    runProgram(myVec);
}

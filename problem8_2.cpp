#include "readFile.hpp"
#include <vector>
#include <set>

using namespace std;

void runInstruction(int &instruction, int &accumulator, const string command, const char sign, const int value)
{

    cout << "Running " << command << sign << " " << value << endl;
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

string swapCommand(string &command)
{
    if (command == "nop")
    {
        return "jmp";
    }

    if (command == "jmp")
    {
        return "nop";
    }

    return "INVALID!";
}

void runProgram(vector<string> &program)
{

    int accumulator = 0, instruction = 0;

    set<int> linesRun;
    set<int> linesSwapped;

    bool swapFlag = true;
    while (true)
    {
        linesRun.insert(instruction);
        string line = program[instruction];
        string command = line.substr(0, 3);
        char sign = line[4];
        int value = stoi(line.substr(5, string::npos));
        if (swapFlag && (command == "jmp" || command == "nop"))
        {
            if (linesSwapped.find(instruction) == linesSwapped.end()) //Then we have not swapped this line before
            {
                swapFlag = false;
                linesSwapped.insert(instruction);
                command = swapCommand(command);
            }
        }

        runInstruction(instruction, accumulator, command, sign, value);

        //Determine if we succeed or if we need to reset
        //If we have run the (new) instruction before, when we need to reset
        if (linesRun.find(instruction) != linesRun.end())
        {
            //Reset everything (except lines swapped)
            linesRun = {};
            accumulator = 0;
            instruction = 0;
            swapFlag = true;
        }

        if (instruction == program.size())
        {
            cout << "Program ended correctly! Accum value is " << accumulator << endl;
            return;
        }
    }
}

int main()
{
    vector<string> myVec = stringVectorFromFile("problem8inputs.txt");

    runProgram(myVec);
}

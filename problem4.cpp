#include "readFile.hpp"
#include <vector>
#include <map>
#include <regex>

using namespace std;

string requiredFields[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

bool validPassportPartOne(map<string, string> passport)
{
    //Must have all required fields except CID
    for (string field : requiredFields)
    {
        if (passport.count(field) != 1)
        {
            return false;
        }
    }
    return true;
}

//Already know we have the required fields at this point
bool validPassportPartTwo(map<string, string> passport)
{
    map<string, string>::iterator it = passport.begin();
    while (it != passport.end())
    {
        string key = it->first;
        string value = it->second;

        if (key == "byr")
        {
            if ((value.length() != 4) || stoi(value) < 1920 || stoi(value) > 2002)
            {
                return false;
            }
        }

        if (key == "iyr")
        {
            if ((value.length() != 4) || stoi(value) < 2010 || stoi(value) > 2020)
            {
                return false;
            }
        }

        if (key == "eyr")
        {
            if ((value.length() != 4) || stoi(value) < 2020 || stoi(value) > 2030)
            {
                return false;
            }
        }

        if (key == "hgt")
        {
            string unit = value.substr(value.length() - 2, 2);
            string measure = value.substr(0, value.find_first_of(unit));
            if (!(unit == "cm" || unit == "in"))
            {
                return false;
            }

            int measurement = stoi(measure);

            if (unit == "cm")
            {
                if (measurement < 150 || measurement > 193)
                {
                    return false;
                }
            }

            if (unit == "in")
            {
                if (measurement < 59 || measurement > 76)
                {
                    return false;
                }
            }
        }

        if (key == "hcl")
        {
            char prefix = value[0];
            if (prefix != '#')
            {
                return false;
            }
            string suffix = value.substr(1, value.length() - 1);
            regex validHcl("[a-f0-9]{6}", regex_constants::ECMAScript);
            if (!regex_match(suffix, validHcl))
            {
                return false;
            }
        }

        if (key == "ecl")
        {
            if (!(value == "amb" || value == "blu" || value == "brn" || value == "gry" || value == "grn" || value == "hzl" || value == "oth"))
            {
                return false;
            }
        }

        if (key == "pid")
        {
            regex validPid("[0-9]{9}", regex_constants::ECMAScript);
            if (!regex_match(value, validPid))
            {
                return false;
            }
        }

        it++;
    }
    return true;
}

int main()
{
    vector<string> myVec = stringVectorFromFile("problem4input.txt");

    vector<map<string, string>> passports;

    regex e("((\\S*):(\\S*))", regex_constants::ECMAScript);

    int validPassports = 0;

    map<string, string> myMap;
    for (int i = 0; i < myVec.size(); i++)
    {
        string line = myVec[i];

        if (line.empty())
        { // new map
            passports.push_back(myMap);
            if (validPassportPartOne(myMap) && validPassportPartTwo(myMap))
            {
                validPassports++;
            }
            // else
            // {
            //     cout << "Invalid\n";
            // }
            myMap = {};
            continue;
        }

        auto matches_begin = sregex_iterator(line.begin(), line.end(), e);
        auto matches_end = sregex_iterator();

        for (std::sregex_iterator i = matches_begin; i != matches_end; ++i)
        {
            std::smatch match = *i;
            std::string match_str = match.str();
            int index = match_str.find_first_of(":");
            string key = match_str.substr(0, index);
            string value = match_str.substr(index + 1, match_str.length() - index);
            myMap[key] = value;
        }
    }
    cout << "Valid passports:  " << validPassports << "\n";
}
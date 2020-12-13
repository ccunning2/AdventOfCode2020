#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> stringVectorFromFile(std::string fileName);
std::vector<int> intVectorFromFile(std::string fileName);
std::vector<long long int> lliVectorFromFile(std::string fileName);

#endif
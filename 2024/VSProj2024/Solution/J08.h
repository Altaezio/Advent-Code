#pragma once

#include <map>

std::string sol08v1(std::string solutionFileName);
std::string sol08v2(std::string solutionFileName); 

std::map<char, std::vector<std::vector<int>>> GetAntennaPositions(std::vector<std::string>& lines);

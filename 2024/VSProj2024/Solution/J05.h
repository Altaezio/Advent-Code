#pragma once

#include <map>

std::string sol05v1(std::string solutionFileName);
std::string sol05v2(std::string solutionFileName);

bool UpdateIsInOrder(std::map<int, std::vector<int>>& rules, std::vector<int>& update);

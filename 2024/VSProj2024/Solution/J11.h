#pragma once

#include <map>

std::string sol11v1(std::string solutionFileName);
std::string sol11v2(std::string solutionFileName);

std::vector<std::string> SplitStones(std::vector<std::string>& stones);

std::vector<std::string> SplitOneStone(std::string stoneStr);

size_t SplitStone_Rec(unsigned long long stone, std::map<unsigned long long, std::vector<long long>>& tree,
	size_t depthLeft);

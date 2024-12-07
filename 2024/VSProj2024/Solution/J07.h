#pragma once

#include <functional>

std::string sol07v1(std::string solutionFileName);
std::string sol07v2(std::string solutionFileName);

bool CanBeEqual(std::vector<std::function<unsigned long long(unsigned long long, unsigned long long)>>& operations,
	std::vector<int>& values, unsigned long long targetValue, bool print = false);

unsigned long long Concatenation(unsigned long long a, unsigned long long b);

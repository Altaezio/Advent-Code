#pragma once
#include <set>
#include <map>

std::string sol19v1(std::string solutionFileName);
std::string sol19v2(std::string solutionFileName);

bool IsPatternPossible(
	const std::set<std::string>& towels,
	const std::string& pattern,
	std::vector<std::set<std::string>>& alreadyVisited,
	size_t start,
	std::vector<std::string>& validTowels);

size_t CountPossiblePatterns(
	const std::set<std::string>& towels,
	const std::string& pattern,
	std::vector<std::map<std::string, size_t>>& alreadyVisited,
	size_t start);

#pragma once

#include <set>

std::string sol10v1(std::string solutionFileName);
std::string sol10v2(std::string solutionFileName);

std::vector<std::vector<size_t>> GetNeighbors(std::vector<std::string>& lines, std::vector<size_t> pos);

std::set<std::vector<size_t>> FindUnique9_Rec(std::vector<std::string>& lines, std::vector<size_t> start);

size_t Find9_Rec(std::vector<std::string>& lines, std::vector<size_t> start);

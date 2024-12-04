#pragma once

#include <vector>
#include <string>

std::string sol04v1(std::string solutionFileName);
std::string sol04v2(std::string solutionFileName);

bool MatchWord(std::vector<std::string>& lines, size_t startRow, size_t startCol, int xDir, int yDir, std::string wordToMatch);
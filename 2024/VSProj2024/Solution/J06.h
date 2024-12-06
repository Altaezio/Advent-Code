#pragma once

std::string sol06v1(std::string solutionFileName);
std::string sol06v2(std::string solutionFileName);

std::vector<int> GetStartingPoint(std::vector<std::string>& lines);
bool DoMove(std::vector<std::string>& lines, std::vector<int>& direction, std::vector<int>& currentPos);

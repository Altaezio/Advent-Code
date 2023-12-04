#pragma once

#include <vector>
#include <string>

std::vector<std::string> getSolutionLines(std::string pathToFile);

void coutList(std::vector<std::string> list);

std::vector<std::string> Extract(const std::string& Text);

std::vector<int> ExtractInt(const std::string& Text);

#pragma once

#include <vector>
#include <string>

std::vector<std::string> getSolutionLines(std::string pathToFile);

void coutList(std::vector<std::string> list);

std::vector<std::string> Extract(const std::string& text);

std::vector<std::string> ExtractWithoutChar(const std::string& text, char charToRemove);

std::vector<int> ExtractInt(const std::string& text);

std::vector<long long> Extractll(const std::string& text);

std::vector<unsigned long long> Extractull(const std::string& text);

std::vector<unsigned long long> ExtractullAmongOther(const std::string& text);

std::vector<long long> ExtractllAmongOther(const std::string& text);

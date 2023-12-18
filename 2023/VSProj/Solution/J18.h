#pragma once

std::string sol18v1();
std::string sol18v2();

std::vector<std::pair<int, int>> digTrench(std::vector<std::string> lines);

int countTrench(std::vector<std::pair<int, int>> trench);

std::vector<std::string> translateLines(std::vector<std::string> lines);

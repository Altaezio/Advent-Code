#pragma once
#include <map>

struct Node;

std::string sol18v1(std::string solutionFileName);
std::string sol18v2(std::string solutionFileName);

Node CreateNode(const std::vector<std::string>& currentMap, std::vector<size_t>position, Node& previousNode, std::vector<size_t>start, std::vector<size_t>end);

size_t PaintPath(std::vector<std::string>& lines, std::map<std::vector<size_t>, Node>& visited, std::vector<size_t> pos);

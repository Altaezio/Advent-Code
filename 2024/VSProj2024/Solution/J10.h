#pragma once

std::string sol10v1(std::string solutionFileName);
std::string sol10v2(std::string solutionFileName);

struct EdgeNode
{
	std::vector<size_t> pos;
	char height;

	EdgeNode(std::vector<size_t> pos, char height) :pos(pos), height(height) {}
};

void Dijkstra(std::vector<std::vector<EdgeNode>>& graph,
	std::vector<std::vector<EdgeNode*>>& parent,
	std::vector<std::vector<size_t>>& distance,
	std::vector<size_t> start);

std::vector<std::vector<EdgeNode>> MakeGraph(std::vector<std::string>& lines);

std::vector<EdgeNode*> GetNeighbors(std::vector<std::vector<EdgeNode>>& graph, std::vector<size_t> pos);

size_t Find9_Rec(std::vector<std::vector<EdgeNode>>& graph, std::vector<size_t> start);

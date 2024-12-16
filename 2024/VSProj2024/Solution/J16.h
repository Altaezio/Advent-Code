#pragma once
#include <AStar.h>
#include <map>

std::string sol16v1(std::string solutionFileName);
std::string sol16v2(std::string solutionFileName);

struct DirectedNode : Node
{
	size_t direction = 0;

	DirectedNode() : Node(3) {}
	DirectedNode(const std::vector<size_t>& position)
		: Node(3, position)
	{
	}
	DirectedNode(const std::vector<size_t>& position, const std::vector<size_t>& previous, long long cost, long long heuristic)
		: Node(3, position, previous, cost, heuristic)
	{
		std::vector<size_t> dir;
		for (size_t i = 0; i < 2; i++)
		{
			dir.push_back((long long)position[i] - (long long)previous[i]);
		}
		if (dir[0] == 1)
		{
			direction = 0;
		}
		else if (dir[0] == -1)
		{
			direction = 1;
		}
		else if (dir[1] == 1)
		{
			direction = 2;
		}
		else if (dir[1] == -1)
		{
			direction = 3;
		}
		this->position.push_back(direction);
	}
};

inline
bool operator==(const DirectedNode& lhs, const DirectedNode& rhs)
{
	return lhs.position == rhs.position && lhs.cost == rhs.cost;
}

DirectedNode CreateNode(
	const std::vector<std::string>& currentMap,
	std::vector<size_t> position,
	DirectedNode& previousNode,
	std::vector<size_t> start,
	std::vector<size_t> end);

size_t PaintPath(std::vector<std::string>& lines, std::map<std::vector<size_t>, DirectedNode>& visited, std::vector<size_t> pos);

#pragma once
#include <vector>
#include <string>
#include <map>

// Generic A* algorithm

struct Node
{
	size_t dimensions = 2;
	std::vector<size_t> position = std::vector<size_t>(dimensions, std::numeric_limits<size_t>::max());
	std::vector<std::vector<size_t>> previous;
	long long cost = std::numeric_limits<long long>::max();
	long long heuristic = std::numeric_limits<long long>::max();
	Node(size_t dimensions = 2) : dimensions(dimensions)
	{
	}
	Node(size_t dimensions, const std::vector<size_t>& position)
		: dimensions(dimensions), position(position)
	{
	}
	Node(size_t dimensions, const std::vector<size_t>& position, const std::vector<size_t>& previous, long long cost, long long heuristic)
		: dimensions(dimensions), position(position), cost(cost), heuristic(heuristic)
	{
		this->previous.push_back(previous);
	}
};

inline
bool operator==(const Node& lhs, const Node& rhs)
{
	return lhs.position == rhs.position && lhs.cost == rhs.cost;
}

std::vector<std::vector<size_t>> SimpleGetNeighbours(const std::vector<std::string>& map, const std::vector<size_t> pos);

bool CompareNodeOnHeuristic(Node a, Node b);

template<class T>
std::vector<T> GetShortestPath(
	const std::vector<std::string>& currentMap,
	std::vector<size_t> objective,
	T start,
	T(*CreateNode)(
		const std::vector<std::string>&,
		std::vector<size_t>,
		T&,
		std::vector<size_t>,
		std::vector<size_t>),
	std::vector<std::vector<size_t>>(*GetNeighbours)(const std::vector<std::string>&, const std::vector<size_t>) = &SimpleGetNeighbours,
	std::map<std::vector<size_t>, T>* closedListOut = nullptr,
	bool visitAll = false)
{
	static_assert(std::is_base_of<Node, T>::value, "T must inherit from Node");

	std::map<std::vector<size_t>, T> closedList;
	std::map<std::vector<size_t>, T> openList;
	openList[start.position] = start;

	T end;
	while (!openList.empty())
	{
		std::vector<size_t> bestPos = openList.begin()->first;
		for (auto it = openList.begin(); it != openList.end(); it++)
		{
			if (it->second.heuristic < openList[bestPos].heuristic)
			{
				bestPos = it->first;
			}
		}
		T bestNode = openList[bestPos];
		openList.erase(bestPos);
		if (bestNode.position == objective)
		{
			if (!closedList.contains(bestNode.position))
			{
				closedList[bestNode.position] = {};
			}
			closedList[bestNode.position] = bestNode;
			if (closedListOut)
			{
				*closedListOut = closedList;
			}
			end = bestNode;
			if (!visitAll)
			{
				break;
			}
		}
		for (std::vector<size_t> n : GetNeighbours(currentMap, bestNode.position))
		{
			T neighbour = CreateNode(currentMap, n, bestNode, start.position, objective);

			if (neighbour.cost == std::numeric_limits<long long>::max())
			{
				continue;
			}
			if (openList.contains(n))
			{
				if (openList[n].cost < neighbour.cost)
				{
					continue;
				}
				else if (openList[n].cost == neighbour.cost &&
					find(openList[n].previous.begin(), openList[n].previous.end(), bestNode) == openList[n].previous.end())
				{
					openList[n].previous.push_back(bestNode.position);
					continue;
				}
			}
			if (closedList.contains(n))
			{
				if (closedList[n].cost == neighbour.cost &&
					find(closedList[n].previous.begin(), closedList[n].previous.end(), bestNode) == closedList[n].previous.end())
				{
					closedList[n].previous.push_back(bestNode.position);
				}
				continue;
			}
			openList[n] = neighbour;
		}
		closedList[bestNode.position] = bestNode;
	}
	if (end.position[0] != std::numeric_limits<size_t>::max())
	{
		return RebuildPath(currentMap, end, closedList, GetNeighbours);
	}
	else
	{
		return {}; // ERROR
	}
}

template<class T>
std::vector<T> RebuildPath(
	const std::vector<std::string>& map,
	T& end,
	std::map<std::vector<size_t>, T>& visitedNodes,
	std::vector<std::vector<size_t>>(*GetNeighbours)(const std::vector<std::string>&, const std::vector<size_t>))
{
	static_assert(std::is_base_of<Node, T>::value, "T must inherit from Node");

	std::vector<T> path;
	path.push_back(end);
	T node = end;
	std::vector<size_t> firstPrevious = node.previous[0];
	while (firstPrevious[0] != std::numeric_limits<size_t>::max())
	{
		T bestPrevious = visitedNodes[firstPrevious];
		path.insert(path.begin(), bestPrevious);
		node = bestPrevious;
	}
	return path;
}
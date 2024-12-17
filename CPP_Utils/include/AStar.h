#pragma once
#include <vector>
#include <string>
#include <map>

// Generic A* algorithm

struct Node
{
	size_t dimensions = 2;
	std::vector<size_t> position = std::vector<size_t>(dimensions, std::numeric_limits<size_t>::max());
	std::vector<std::vector<size_t>> previous{};
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

std::vector<std::vector<size_t>> SimpleGetNeighbours2D(const std::vector<std::string>& map, const std::vector<size_t> pos);

bool CompareNodeOnHeuristic(Node a, Node b);

template<class T>
std::vector<T> GetShortestPath(
	const std::vector<std::string>& currentMap,
	T& start,
	T& objective,
	bool (*IsAtObjective)(const T&, const T&),
	T(*CreateNode)(
		const std::vector<std::string>&,
		std::vector<size_t>,
		T&,
		std::vector<size_t>,
		std::vector<size_t>),
	std::vector<std::vector<size_t>>(*GetNeighbours)(const std::vector<std::string>&, const std::vector<size_t>) = &SimpleGetNeighbours2D,
	std::map<std::vector<size_t>, T>* closedListOut = nullptr,
	bool visitAll = false)
{
	static_assert(std::is_base_of<Node, T>::value, "T must inherit from Node");

	std::map<std::vector<size_t>, T> closedList;
	std::map<std::vector<size_t>, T> openList;
	openList[start.position] = start;

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
		if (IsAtObjective(objective, bestNode) && bestNode.cost <= objective.cost)
		{
			if (bestNode.cost < objective.cost)
			{
				objective.previous.clear();
				objective.cost = bestNode.cost;
			}

			objective.previous.assign(bestNode.previous.begin(), bestNode.previous.end());

			if (!visitAll)
			{
				break;
			}
		}
		for (std::vector<size_t> n : GetNeighbours(currentMap, bestNode.position))
		{
			T neighbour = CreateNode(currentMap, n, bestNode, start.position, objective.position);

			if (neighbour.cost == std::numeric_limits<long long>::max())
			{
				continue;
			}
			if (openList.contains(neighbour.position))
			{
				if (openList[neighbour.position].cost < neighbour.cost)
				{
					continue;
				}
				else if (openList[neighbour.position].cost == neighbour.cost &&
					find(openList[neighbour.position].previous.begin(), openList[neighbour.position].previous.end(), bestNode) == openList[neighbour.position].previous.end())
				{
					openList[neighbour.position].previous.push_back(bestNode.position);
					continue;
				}
			}
			if (closedList.contains(neighbour.position))
			{
				if (closedList[neighbour.position].cost == neighbour.cost &&
					find(closedList[neighbour.position].previous.begin(), closedList[neighbour.position].previous.end(), bestNode) == closedList[neighbour.position].previous.end())
				{
					closedList[neighbour.position].previous.push_back(bestNode.position);
				}
				continue;
			}
			openList[neighbour.position] = neighbour;
		}
		closedList[bestNode.position] = bestNode;
	}
	if (closedListOut)
	{
		*closedListOut = closedList;
	}
	if (objective.previous.size() != 0)
	{
		return RebuildPath(currentMap, objective, closedList, GetNeighbours);
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
	while (node.previous.size() > 0 && node.previous[0][0] != std::numeric_limits<size_t>::max())
	{
		T bestPrevious = visitedNodes[node.previous[0]];
		path.insert(path.begin(), bestPrevious);
		node = bestPrevious;
	}
	return path;
}
#include <FileHandler.h>
#include <iostream>
#include <AStar.h>
#include "J18.h"

using namespace std;

string sol18v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<size_t> spaceSize{ 71,71 };
	size_t corruptionLevel = 1024;
	if (solutionFileName == "test")
	{
		spaceSize = { 7,7 };
		corruptionLevel = 12;
	}
	vector<string> space;
	for (size_t y = 0; y < spaceSize[1]; y++)
	{
		string line(spaceSize[0], '.');
		space.push_back(line);
	}
	for (size_t i = 0; i < corruptionLevel; i++)
	{
		size_t comma = lines[i].find(',');
		vector<size_t> pos;
		pos.push_back(stoull(lines[i].substr(0, comma)));
		pos.push_back(stoull(lines[i].substr(comma + 1, lines[i].size() - comma)));
		space[pos[1]][pos[0]] = '#';
	}

	Node start(2, { 0,0 }, 0, 0);
	Node end(2, { spaceSize[0] - 1,spaceSize[1] - 1 });
	vector<Node> path = GetShortestPath<Node>(space, start, end, CreateNode);
	return to_string(end.cost);
}

Node CreateNode(const vector<string>& currentMap, vector<size_t>position, Node& previousNode, vector<size_t>start, vector<size_t>end)
{
	long long cost = numeric_limits<long long>::max();
	long long h = numeric_limits<long long>::max();
	if (currentMap[position[1]][position[0]] != '#')
	{
		cost = previousNode.cost + 1;
		h = end[0] - position[0] + end[1] - position[1];
	}
	return Node(2, position, cost, h, previousNode.position);
}

size_t PaintPath(vector<string>& lines, map<vector<size_t>, Node>& visited, vector<size_t> pos)
{
	size_t count = 0;
	if (lines[pos[1]][pos[0]] != 'O')
	{
		count = 1;
		lines[pos[1]][pos[0]] = 'O';
	}
	vector<vector<size_t>> previous = visited[pos].previous;
	visited.erase(pos);
	for (auto it = previous.begin(); it != previous.end(); it++)
	{
		count += PaintPath(lines, visited, *it);
	}
	return count;
}

#include <FileHandler.h>
#include <AStar.h>
#include <iostream>
#include <numbers>
#include "J16.h"

using namespace std;

string sol16v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<size_t> start;
	vector<size_t> end;
	for (size_t y = 0; y < lines.size(); y++)
	{
		for (size_t x = 0; x < lines[y].size(); x++)
		{
			if (lines[y][x] == 'S')
			{
				start.push_back(x);
				start.push_back(y);
			}
			if (lines[y][x] == 'E')
			{
				end.push_back(x);
				end.push_back(y);
			}
			if (start.size() > 0 && end.size() > 0)
			{
				break;
			}
		}
	}
	map<char, long long> costs;
	costs['#'] = numeric_limits<long long>::max();
	costs['.'] = 1;
	costs['E'] = 1;
	costs['S'] = numeric_limits<long long>::max();

	map<vector<size_t>, DirectedNode> visited;
	vector<DirectedNode> bestPath = GetShortestPath<DirectedNode>(lines, end, start, CreateNode, SimpleGetNeighbours, &visited);
	for (auto it = visited.begin(); it != visited.end(); it++)
	{
		lines[it->first[1]][it->first[0]] = '|';
	}
	char previousChar = '>';
	size_t nturns = 0;
	for (DirectedNode& n : bestPath)
	{
		if (n.position[2] == 0)
			lines[n.position[1]][n.position[0]] = '>';
		else if (n.position[2] == 1)
			lines[n.position[1]][n.position[0]] = '<';
		else if (n.position[2] == 2)
			lines[n.position[1]][n.position[0]] = 'v';
		else if (n.position[2] == 3)
			lines[n.position[1]][n.position[0]] = '^';

		if (previousChar != lines[n.position[1]][n.position[0]])
		{
			nturns++;
			previousChar = lines[n.position[1]][n.position[0]];
		}
	}
	if (solutionFileName == "test")
	{
		coutList(lines);
	}
	cout << "Path length: " << bestPath.size() << "\nTurns: " << nturns << endl;
	return to_string(bestPath.back().cost);
}

DirectedNode CreateNode(
	const vector<string>& currentMap,
	vector<size_t> position,
	DirectedNode& previousNode,
	vector<size_t> start,
	vector<size_t> end)
{
	long long cost = numeric_limits<long long>::max();
	if (currentMap[position[1]][position[0]] == '#' ||
		position == previousNode.position)
	{
		cost = numeric_limits<long long>::max();
	}
	else
	{
		cost = previousNode.cost;
		vector<long long> dir{ 0,0 };
		vector<long long> dirBefore;
		if (previousNode.direction == 0)
		{
			dirBefore = { 1,0 };
		}
		else if (previousNode.direction == 1)
		{
			dirBefore = { -1,0 };
		}
		else if (previousNode.direction == 2)
		{
			dirBefore = { 0,1 };
		}
		else if (previousNode.direction == 3)
		{
			dirBefore = { 0,-1 };
		}
		for (size_t i = 0; i < 2; i++)
		{
			dir[i] = (long long)position[i] - (long long)previousNode.position[i];
		};
		long long dot = dir[0] * dirBefore[0] + dir[1] * dirBefore[1];
		long long det = dir[0] * dirBefore[1] - dir[1] * dirBefore[0];
		double angle = atan2(det, dot);
		if (angle == 0.0)
		{
			cost += 1;
		}
		else if (angle == numbers::pi / 2 || angle == -numbers::pi / 2)
		{
			cost += 1001;
		}
	}
	long long heuristic = cost;
	return DirectedNode(position, previousNode.position, cost, heuristic);
}

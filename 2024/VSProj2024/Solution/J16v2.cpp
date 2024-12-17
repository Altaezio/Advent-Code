#include <FileHandler.h>
#include <iostream>
#include "J16.h"

using namespace std;

string sol16v2(string solutionFileName)
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
	start.push_back(0);
	DirectedNode startNode(start);
	startNode.cost = 0;
	startNode.heuristic = 0;
	DirectedNode endNode(end);
	endNode.position.push_back(0);
	map<char, long long> costs;
	costs['#'] = numeric_limits<long long>::max();
	costs['.'] = 1;
	costs['E'] = 1;
	costs['S'] = numeric_limits<long long>::max();

	map<vector<size_t>, DirectedNode> visited;
	vector<DirectedNode> bestPath = GetShortestPath<DirectedNode>(lines, startNode, endNode, IsAtObjective, CreateNode, SimpleGetNeighbours2D, &visited, true);
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
	visited[endNode.position] = endNode;
	size_t seats = PaintPath(lines, visited, endNode.position);
	if (solutionFileName == "test")
	{
		coutList(lines);
	}
	cout << "Path length: " << bestPath.size() << "\nTurns: " << nturns << endl;
	return to_string(seats);
}

size_t PaintPath(vector<string>& lines, map<vector<size_t>, DirectedNode>& visited, vector<size_t> pos)
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

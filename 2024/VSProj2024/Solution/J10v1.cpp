#include <FileHandler.h>
#include <iostream>
#include "J10.h"

using namespace std;

string sol10v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<vector<EdgeNode>> graph = MakeGraph(lines);
	vector<vector<EdgeNode*>> parent;
	vector<vector<size_t>> distance;
	size_t sum = 0;
	for (size_t y = 0; y < lines.size(); y++)
	{
		string line = lines[y];
		for (size_t x = 0; x < line.size(); x++)
		{
			if (line[x] == '0')
			{
				Dijkstra(graph, parent, distance, { x,y });
				for (vector<size_t> lineDist : distance)
				{
					for (size_t dist : lineDist)
					{
						if (dist == 9)
						{
							sum++;
						}
					}
				}
			}
		}
	}
	return to_string(sum);
}

vector<vector<EdgeNode>> MakeGraph(vector<string>& lines)
{
	vector<vector<EdgeNode>> graph;
	for (size_t y = 0; y < lines.size(); y++)
	{
		string line = lines[y];
		vector<EdgeNode> edges;
		for (size_t x = 0; x < line.size(); x++)
		{
			char c = line[x];
			EdgeNode node({ x,y }, c);
			edges.push_back(node);
		}
		graph.push_back(edges);
	}
	return graph;
}

vector<EdgeNode*> GetNeighbors(vector<vector<EdgeNode>>& graph, vector<size_t> pos)
{
	vector<EdgeNode*> neighbors;
	EdgeNode* current = &graph[pos[1]][pos[0]];
	if (pos[0] > 0)
	{
		EdgeNode* n = &graph[pos[1]][pos[0] - 1];
		if (n->height == current->height + 1)
			neighbors.push_back(n);
	}
	if (pos[1] > 0)
	{
		EdgeNode* n = &graph[pos[1] - 1][pos[0]];
		if (n->height == current->height + 1)
			neighbors.push_back(n);
	}
	if (pos[0] + 1 < graph[pos[1]].size())
	{
		EdgeNode* n = &graph[pos[1]][pos[0] + 1];
		if (n->height == current->height + 1)
			neighbors.push_back(n);
	}
	if (pos[1] + 1 < graph.size())
	{
		EdgeNode* n = &graph[pos[1] + 1][pos[0]];
		if (n->height == current->height + 1)
			neighbors.push_back(n);
	}
	return neighbors;
}

void Dijkstra(vector<vector<EdgeNode>>& graph, vector<vector<EdgeNode*>>& parent, vector<vector<size_t>>& distance, vector<size_t> start)
{
	vector<vector<bool>> discovered;
	parent.clear();
	distance.clear();
	for (vector<EdgeNode> line : graph)
	{
		vector<EdgeNode*> parentLine(line.size(), nullptr);
		parent.push_back(parentLine);
		vector<size_t> distanceLine(line.size(), numeric_limits<size_t>::max());
		distance.push_back(distanceLine);
		vector<bool> discoveredLine(line.size(), false);
		discovered.push_back(discoveredLine);
	}
	EdgeNode* current;
	vector<size_t> currentPos = start;
	distance[start[1]][start[0]] = 0;

	while (!discovered[currentPos[1]][currentPos[0]])
	{
		discovered[currentPos[1]][currentPos[0]] = true;
		current = &graph[currentPos[1]][currentPos[0]];

		vector<EdgeNode*> neighbors = GetNeighbors(graph, currentPos);
		for (EdgeNode* n : neighbors)
		{
			if (distance[currentPos[1]][currentPos[0]] < distance[n->pos[1]][n->pos[0]])
			{
				distance[n->pos[1]][n->pos[0]] = distance[currentPos[1]][currentPos[0]] + 1;
				parent[n->pos[1]][n->pos[0]] = current;
			}
		}
		if (neighbors.size() > 0)
		{
			current = neighbors.back();
		}

		size_t smallestDist = numeric_limits<size_t>::max();
		for (size_t i = 0; i < distance.size(); i++)
		{
			for (size_t j = 0; j < distance[i].size(); j++)
			{
				if (!discovered[i][j] && distance[i][j] < smallestDist)
				{
					currentPos = { j, i };
					smallestDist = distance[i][j];
				}
			}
		}
	}
}

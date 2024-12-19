#include <FileHandler.h>
#include <iostream>
#include <AStar.h>
#include "J18.h"

using namespace std;

string sol18v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<size_t> spaceSize{ 71,71 };
	if (solutionFileName == "test")
	{
		spaceSize = { 7,7 };
	}
	vector<string> space;
	for (size_t y = 0; y < spaceSize[1]; y++)
	{
		string line(spaceSize[0], '.');
		space.push_back(line);
	}

	vector<vector<size_t>> currentPath;
	size_t i = 0;
	for (; i < lines.size(); i++)
	{
		size_t comma = lines[i].find(',');
		vector<size_t> pos;
		pos.push_back(stoull(lines[i].substr(0, comma)));
		pos.push_back(stoull(lines[i].substr(comma + 1, lines[i].size() - comma)));
		space[pos[1]][pos[0]] = '#';
		if (currentPath.size() == 0 || find(currentPath.begin(), currentPath.end(), pos) != currentPath.end())
		{
			Node start(2, { 0,0 }, 0, 0);
			Node end(2, { spaceSize[0] - 1,spaceSize[1] - 1 });
			vector<Node> path = GetShortestPath<Node>(space, start, end, CreateNode);
			if (path.size() == 0)
			{
				break;
			}
			currentPath.clear();
			for (Node& node : path)
			{
				currentPath.push_back(node.position);
			}
		}
		cout << "\rCorruption: " << i;
	}
	cout << "\rCorruption: " << i << " blocking a path of " << currentPath.size() - 1 << " steps" << endl;
	for (vector<size_t> point : currentPath)
	{
		space[point[1]][point[0]] = 'O';
	}
	coutList(space);
	return lines[i];
}
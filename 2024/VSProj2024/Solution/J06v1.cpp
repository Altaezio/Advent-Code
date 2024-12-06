#include <FileHandler.h>
#include <iostream>
#include <set>
#include "J06.h"

using namespace std;

string sol06v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	set<vector<int>> visited;
	// find starting point
	vector<int> currentPos = GetStartingPoint(lines);
	if (currentPos[0] == -1 || currentPos[1] == -1)
	{
		return "Start not found";
	}

	visited.insert(currentPos);
	vector<int> direction{ 0, -1 };
	// make the moves
	while (currentPos[0] >= 0 &&
		currentPos[1] >= 0 &&
		currentPos[1] < lines.size() &&
		currentPos[0] < lines[currentPos[1]].size())
	{
		if (DoMove(lines, direction, currentPos))
		{
			visited.insert(currentPos);
		}
	}
	return to_string(visited.size());
}

vector<int> GetStartingPoint(vector<string>& lines)
{
	for (int y = 0; y < lines.size(); y++)
	{
		string line = lines[y];
		for (int x = 0; x < line.size(); x++)
		{
			if (line[x] == '^')
				return { x, y };
		}
	}
	return { -1, -1 };
}

bool DoMove(vector<string>& lines, vector<int>& direction, vector<int>& currentPos)
{
	vector<int> nextPos{ currentPos[0] + direction[0], currentPos[1] + direction[1] };

	if (nextPos[0] < 0 ||
		nextPos[1] < 0 ||
		nextPos[1] >= lines.size() ||
		nextPos[0] >= lines[nextPos[1]].size())
	{
		currentPos = nextPos;
		return false;
	}

	if (lines[nextPos[1]][nextPos[0]] == '#')
	{
		direction = { -direction[1], direction[0] };
		return false;
	}

	currentPos = nextPos;
	return true;
}

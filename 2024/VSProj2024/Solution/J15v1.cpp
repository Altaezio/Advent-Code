#include <FileHandler.h>
#include <iostream>
#include "J15.h"

using namespace std;

string sol15v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<string> currentMap;
	vector<size_t> startPos;
	vector<size_t> currentPos;
	bool inMap = true;
	for (size_t y = 0; y < lines.size(); y++)
	{
		string line = lines[y];
		if (line.size() < 2)
		{
			inMap = false;
			currentPos = startPos;
			continue;
		}
		if (inMap)
		{
			currentMap.push_back(line);
			if (startPos.size() == 0)
			{
				size_t start = line.find('@');
				if (start != string::npos)
				{
					startPos.push_back(start);
					startPos.push_back(y);
				}
			}
		}
		else
		{
			for (char c : line)
			{
				currentPos = MoveRobotOrCreate(currentMap, currentPos, c);
			}
		}
	}
	if (solutionFileName == "test")
	{
		coutList(currentMap);
	}
	size_t sum = 0;
	for (size_t y = 0; y < currentMap.size(); y++)
	{
		for (size_t x = 0; x < currentMap[y].size(); x++)
		{
			if (currentMap[y][x] == 'O')
			{
				sum += 100 * y + x;
			}
		}
	}
	return to_string(sum);
}

vector<size_t> MoveRobotOrCreate(vector<string>& map, const vector<size_t>& position, char direction)
{
	vector<size_t> newPos = position;
	if (direction == '^')
	{
		newPos[1] -= 1;
	}
	else if (direction == 'v')
	{
		newPos[1] += 1;

	}
	else if (direction == '<')
	{
		newPos[0] -= 1;
	}
	else if (direction == '>')
	{
		newPos[0] += 1;
	}

	if (map[newPos[1]][newPos[0]] == '#')
	{
		return position;
	}
	bool canMove = true;
	if (map[newPos[1]][newPos[0]] == 'O')
	{
		vector<size_t> newCreatePos = MoveRobotOrCreate(map, newPos, direction);
		canMove = newCreatePos[0] != newPos[0] || newCreatePos[1] != newPos[1];
	}
	if (canMove)
	{
		map[newPos[1]][newPos[0]] = map[position[1]][position[0]];
		map[position[1]][position[0]] = '.';
		return newPos;
	}
	else
	{
		return position;
	}
}
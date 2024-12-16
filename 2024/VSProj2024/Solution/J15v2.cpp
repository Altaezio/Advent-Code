#include <FileHandler.h>
#include <iostream>
#include "J15.h"

using namespace std;

string sol15v2(string solutionFileName)
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
			string newLine;
			for (size_t x = 0; x < line.size(); x++)
			{
				if (lines[y][x] == '#')
				{
					newLine.append("##");
				}
				else if (lines[y][x] == 'O')
				{
					newLine.append("[]");
				}
				else if (lines[y][x] == '.')
				{
					newLine.append("..");
				}
				else if (lines[y][x] == '@')
				{
					newLine.append("@.");
					startPos.push_back(2 * x);
					startPos.push_back(y);
				}
			}
			currentMap.push_back(newLine);
		}
		else
		{
			for (char c : line)
			{
				if (CanMoveRobotOrBigCreate(currentMap, currentPos, c))
				{
					DoMoveRobotOrBigCreate(currentMap, currentPos, c);
				}
			}
		}
	}

	coutList(currentMap);

	size_t sum = 0;
	for (size_t y = 0; y < currentMap.size(); y++)
	{
		for (size_t x = 0; x < currentMap[y].size(); x++)
		{
			if (currentMap[y][x] == '[')
			{
				sum += 100 * y + x;
			}
		}
	}
	return to_string(sum);
}

bool CanMoveRobotOrBigCreate(vector<string>& map, vector<size_t>& position, char direction)
{
	vector<size_t> newPos = position;
	vector<size_t> posLeft = position;
	vector<size_t> posRight = position;
	bool positionIsCreate = false;
	vector<size_t> newPosLeft = newPos;
	vector<size_t> newPosRight = newPos;
	if (map[position[1]][position[0]] == '[')
	{
		map[newPos[1]][newPos[0]] = '.';
		map[newPos[1]][newPos[0] + 1] = '.';
		newPosRight[0]++;
		positionIsCreate = true;
	}
	else if (map[position[1]][position[0]] == ']')
	{
		map[newPos[1]][newPos[0]] = '.';
		map[newPos[1]][newPos[0] - 1] = '.';
		posLeft[0]--;
		newPosLeft = posLeft;
		positionIsCreate = true;
	}
	if (direction == '^')
	{
		newPos[1]--;
		newPosLeft[1]--;
		newPosRight[1]--;
	}
	else if (direction == 'v')
	{
		newPos[1]++;
		newPosLeft[1]++;
		newPosRight[1]++;
	}
	else if (direction == '<')
	{
		newPos[0]--;
		newPosLeft[0]--;
		newPosRight[0]--;
	}
	else if (direction == '>')
	{
		newPos[0]++;
		newPosLeft[0]++;
		newPosRight[0]++;
	}
	bool newLeftIsCreate = false;
	bool newRightIsCreate = false;
	if (map[newPosLeft[1]][newPosLeft[0]] == ']' || map[newPosLeft[1]][newPosLeft[0]] == '[')
	{
		newLeftIsCreate = true;
	}
	if (positionIsCreate && map[newPosRight[1]][newPosRight[0]] == '[')
	{
		newRightIsCreate = true;
	}

	if (map[newPosLeft[1]][newPosLeft[0]] == '#' || map[newPosRight[1]][newPosRight[0]] == '#')
	{
		if (positionIsCreate)
		{
			map[posLeft[1]][posLeft[0]] = '[';
			map[posLeft[1]][posLeft[0] + 1] = ']';
		}
		return false;
	}

	bool canMoveLeft = true;
	bool canMoveRight = true;
	if (newLeftIsCreate)
	{
		canMoveLeft = CanMoveRobotOrBigCreate(map, newPosLeft, direction);
	}
	if (canMoveLeft && newRightIsCreate)
	{
		canMoveRight = CanMoveRobotOrBigCreate(map, newPosRight, direction);
	}

	if (positionIsCreate)
	{
		map[posLeft[1]][posLeft[0]] = '[';
		map[posLeft[1]][posLeft[0] + 1] = ']';
	}
	return canMoveLeft && canMoveRight;
}

void DoMoveRobotOrBigCreate(vector<string>& map, vector<size_t>& position, char direction)
{
	vector<size_t> newPos = position;
	vector<size_t> posLeft = position;
	vector<size_t> posRight = position;
	bool positionIsCreate = false;
	vector<size_t> newPosLeft = newPos;
	vector<size_t> newPosRight = newPos;
	if (map[position[1]][position[0]] == '[')
	{
		map[newPos[1]][newPos[0]] = '.';
		map[newPos[1]][newPos[0] + 1] = '.';
		newPosRight[0]++;
		positionIsCreate = true;
	}
	else if (map[position[1]][position[0]] == ']')
	{
		map[newPos[1]][newPos[0]] = '.';
		map[newPos[1]][newPos[0] - 1] = '.';
		posLeft[0]--;
		newPosLeft = posLeft;
		positionIsCreate = true;
	}
	if (direction == '^')
	{
		newPos[1]--;
		newPosLeft[1]--;
		newPosRight[1]--;
	}
	else if (direction == 'v')
	{
		newPos[1]++;
		newPosLeft[1]++;
		newPosRight[1]++;
	}
	else if (direction == '<')
	{
		newPos[0]--;
		newPosLeft[0]--;
		newPosRight[0]--;
	}
	else if (direction == '>')
	{
		newPos[0]++;
		newPosLeft[0]++;
		newPosRight[0]++;
	}
	bool newLeftIsCreate = false;
	bool newRightIsCreate = false;
	if (map[newPosLeft[1]][newPosLeft[0]] == ']' || map[newPosLeft[1]][newPosLeft[0]] == '[')
	{
		newLeftIsCreate = true;
	}
	if (positionIsCreate && map[newPosRight[1]][newPosRight[0]] == '[')
	{
		newRightIsCreate = true;
	}

	bool canMoveLeft = true;
	bool canMoveRight = true;
	if (newLeftIsCreate)
	{
		DoMoveRobotOrBigCreate(map, newPosLeft, direction);
	}
	if (newRightIsCreate)
	{
		DoMoveRobotOrBigCreate(map, newPosRight, direction);
	}

	if (positionIsCreate)
	{
		map[newPosLeft[1]][newPosLeft[0]] = '[';
		map[newPosLeft[1]][newPosLeft[0] + 1] = ']';
	}
	else
	{
		map[newPos[1]][newPos[0]] = map[position[1]][position[0]];
		map[position[1]][position[0]] = '.';
		position = newPos;
	}
}


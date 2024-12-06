#include <FileHandler.h>
#include <iostream>
#include <map>
#include <set>
#include "J06.h"

using namespace std;

string sol06v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<pair<vector<int>, vector<int>>> visited; // path and directions
	// find starting point
	vector<int> startPos = GetStartingPoint(lines);
	vector<int> currentPos = startPos;
	if (currentPos[0] == -1 || currentPos[1] == -1)
	{
		return "Start not found";
	}
	vector<int> startDir{ 0, -1 };
	vector<int> direction = startDir;

	// solve first without obstacle
	visited.push_back(make_pair(startPos, startDir));
	while (currentPos[0] >= 0 &&
		currentPos[1] >= 0 &&
		currentPos[1] < lines.size() &&
		currentPos[0] < lines[currentPos[1]].size())
	{
		if (DoMove(lines, direction, currentPos))
		{
			visited.push_back({ currentPos, direction });
		}
	}

	set<vector<int>> workingObstruction;
	for (auto it = visited.begin() + 1; it != visited.end(); it++)
	{
		vector<int> obstructedPos = it->first;
		lines[obstructedPos[1]].replace(obstructedPos[0], 1, 1, '#');

		currentPos = startPos;
		direction = startDir;
		vector<pair<vector<int>, vector<int>>> newVisited;
		newVisited.push_back(make_pair(currentPos, direction));

		while ((currentPos[0] >= 0 &&
			currentPos[1] >= 0 &&
			currentPos[1] < lines.size() &&
			currentPos[0] < lines[currentPos[1]].size()))
		{
			if (DoMove(lines, direction, currentPos))
			{
				if (find(newVisited.begin(), newVisited.end(), make_pair(currentPos, direction)) != newVisited.end())
				{
					workingObstruction.insert(obstructedPos);
					break;
				}
				else
				{
					newVisited.push_back({ currentPos, direction });
				}
			}
		}
		lines[obstructedPos[1]].replace(obstructedPos[0], 1, 1, '.');
		cout << '\r' << "visited " << (int)(it - visited.begin()) + 1 << "/" << visited.size();
	}
	cout << endl;

	return to_string(workingObstruction.size());
}

#include <iostream>
#include <map>
#include "../FileHandler.h"
#include "J18.h"

using namespace std;

string sol18v1()
{
	vector<string> lines = getSolutionLines("J18");

	vector<pair<int, int>> trench = digTrench(lines);
	int sum = countTrench(trench);
	return to_string(sum);
}

vector<pair<int, int>> digTrench(vector<string> lines)
{
	vector<pair<int,int>> trench;
	pair<int, int> currentCoord;
	currentCoord = make_pair(0, 0);
	trench.push_back(currentCoord);
	for (string line : lines)
	{
		vector<string> splitLIne = Extract(line);
		string direction = splitLIne[0];
		int iterations = stoi(splitLIne[1]);
		pair<int, int> directionPair = make_pair(0, 0);
		if (direction == "L")
		{
			directionPair.second = -1 * iterations;
		}
		else if (direction == "R")
		{
			directionPair.second = 1 * iterations;
		}
		else if (direction == "U")
		{
			directionPair.first = -1 * iterations;
		}
		else if (direction == "D")
		{
			directionPair.first = 1 * iterations;
		}

		currentCoord = make_pair(currentCoord.first + directionPair.first, currentCoord.second + directionPair.second);
		trench.push_back(currentCoord);
	}
	return trench;
}

int countTrench(vector<pair<int, int>> trench)
{
	int area = 0;
	int border = 0;
	for (size_t i = 0; i < trench.size() - 1; i++)
	{
		area += abs(trench[i].second * trench[i + 1].first - trench[i].first * trench[i + 1].second);
		border += abs(trench[i + 1].first - trench[i].first) + abs(trench[i + 1].second - trench[i].second);
	}
	area += (trench.back().second * trench[0].first - trench.back().first * trench[0].second);
	area /= 2;
	int inside = area - border / 2 + 1;
	return inside + border;
}

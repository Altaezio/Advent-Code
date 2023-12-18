#include <iostream>
#include <map>
#include "../FileHandler.h"
#include "J18.h"

using namespace std;

string sol18v1()
{
	vector<string> lines = getSolutionLines("test");

	vector<vector<string>> trench = digTrench(lines);
	int sum = countTrench(trench);
	return to_string(sum);
}

vector<vector<string>> digTrench(vector<string> lines)
{
	map<pair<int,int>, string> trench;
	pair<int, int> upperLeft, lowerRight, currentCoord;
	currentCoord = make_pair(0, 0);
	upperLeft = currentCoord;
	lowerRight = currentCoord;
	trench[currentCoord] = "#";
	for (string line : lines)
	{
		vector<string> splitLIne = Extract(line);
		string direction = splitLIne[0];
		int iterations = stoi(splitLIne[1]);
		string color = splitLIne[2];
		pair<int, int> directionPair = make_pair(0, 0);
		if (direction == "L")
		{
			directionPair.second = -1;
		}
		else if (direction == "R")
		{
			directionPair.second = 1;
		}
		else if (direction == "U")
		{
			directionPair.first = -1;
		}
		else if (direction == "D")
		{
			directionPair.first = 1;
		}
		
		for (size_t i = 0; i < iterations; i++)
		{
			currentCoord = make_pair(currentCoord.first + directionPair.first, currentCoord.second + directionPair.second);
			trench[currentCoord] = "#";
		}

		lowerRight.first = max(currentCoord.first, lowerRight.first);
		lowerRight.second = max(currentCoord.second, lowerRight.second);

		upperLeft.first = min(currentCoord.first, upperLeft.first);
		upperLeft.second = min(currentCoord.second, upperLeft.second);
	}
	vector<vector<string>> trenchVector(lowerRight.first - upperLeft.first + 2, vector<string>(lowerRight.second - upperLeft.second + 2, "."));
	for (auto const& [key, value] : trench)
	{
		trenchVector[get<0>(key) - upperLeft.first][get<1>(key) - upperLeft.second] = value;
	}
	return trenchVector;
}

int countTrench(vector<vector<string>> trench)
{
	int sum = 0;
	for (vector<string> line : trench)
	{
		int lineSum = 0;
		bool inside = false;
		for (string c : line)
		{
			if (c == ".")
			{
				continue;
			}

			if (inside)
			{
				sum += lineSum + 1;
				lineSum = 0;
				inside = false;
			}
			else
			{
				lineSum += 1;
				inside = true;
			}
		}
	}
	return sum;
}

#include <iostream>
#include <map>
#include "../FileHandler.h"
#include "J8.h"

using namespace std;

string sol8v1()
{
	vector<string> lines = getSolutionLines("J8");

	vector<int> directions = RLtoInt(lines[0]);

	map<string, vector<string>> nodes;
	for (size_t lineIndex = 2; lineIndex < lines.size(); lineIndex++)
	{
		string node = lines[lineIndex].substr(0, 3);
		string left = lines[lineIndex].substr(7, 3);
		string right = lines[lineIndex].substr(12, 3);
		nodes[node] = vector{ left, right };
	}

	string currentNode = "AAA";
	size_t step = 0;
	size_t directionIndex = 0;
	do
	{
		currentNode = nodes[currentNode][directions[directionIndex]];
		step++;
		directionIndex = (directionIndex + 1) % directions.size();
	} while (currentNode != "ZZZ");

	return to_string(step);
}

vector<int> RLtoInt(string line)
{
	vector<int> vector;
	for (char& c : line)
	{
		if (c == 'R')
		{
			vector.push_back(1);
		}
		else if (c == 'L')
		{
			vector.push_back(0);
		}
	}
	return vector;
}

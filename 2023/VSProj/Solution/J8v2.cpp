#include <iostream>
#include <map>
#include <numeric>
#include "../FileHandler.h"
#include "J8.h"

using namespace std;

string sol8v2()
{
	vector<string> lines = getSolutionLines("J8");

	vector<int> directions = RLtoInt(lines[0]);

	map<string, vector<string>> nodes;
	vector<string> startingNodes;
	for (size_t lineIndex = 2; lineIndex < lines.size(); lineIndex++)
	{
		string node = lines[lineIndex].substr(0, 3);
		if (node[2] == 'A')
		{
			startingNodes.push_back(node);
		}
		string left = lines[lineIndex].substr(7, 3);
		string right = lines[lineIndex].substr(12, 3);
		nodes[node] = vector{ left, right };
	}

	vector<size_t> steps;
	for (string startingNode : startingNodes)
	{
		string currentNode = startingNode;
		size_t step = 0;
		size_t directionIndex = 0;
		do
		{
			currentNode = nodes[currentNode][directions[directionIndex]];
			step++;
			directionIndex = (directionIndex + 1) % directions.size();
		} while (currentNode[2] != 'Z');
		steps.push_back(step);
	}
	size_t lcmResult = 1;
	for (size_t step : steps)
	{
		lcmResult = lcm(lcmResult, step);
	}
	return to_string(lcmResult);
}

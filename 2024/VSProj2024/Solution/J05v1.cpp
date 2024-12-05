#include <FileHandler.h>
#include <iostream>
#include <algorithm>
#include <map>
#include "J05.h"

using namespace std;

string sol05v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	map<int, vector<int>> orderingRules;
	bool pageOrdering = true;
	int sum = 0;
	for (string line : lines)
	{
		if (pageOrdering && line.size() < 2)
		{
			pageOrdering = false;
			continue;
		}
		if (pageOrdering)
		{
			replace(line.begin(), line.end(), '|', ' ');
			vector<int> rule = ExtractInt(line);
			orderingRules[rule[0]].push_back(rule[1]);
			continue;
		}

		replace(line.begin(), line.end(), ',', ' ');
		vector<int> update = ExtractInt(line);
		if (UpdateIsInOrder(orderingRules, update))
		{
			size_t middleInd = (update.size() - 1) / 2;
			sum += update[middleInd];
		}
	}
	return to_string(sum);
}

bool UpdateIsInOrder(map<int, vector<int>>& rules, vector<int>& update)
{
	for (size_t pageInd = 0; pageInd < update.size(); pageInd++)
	{
		int page = update[pageInd];
		vector<int> pageRules = rules[page];
		for (int after : pageRules)
		{
			for (size_t otherInd = 0; otherInd < pageInd; otherInd++)
			{
				if (update[otherInd] == after)
				{
					return false;
				}
			}
		}
	}
	return true;
}

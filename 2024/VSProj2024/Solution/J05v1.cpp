#include <FileHandler.h>
#include <iostream>
#include <algorithm>
#include "J05.h"

using namespace std;

string sol05v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<vector<int>> orderingRules;
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
			orderingRules.push_back(ExtractInt(line));
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

bool UpdateIsInOrder(vector<vector<int>>& rules, vector<int>& update)
{
	for (size_t pageInd = 0; pageInd < update.size(); pageInd++)
	{
		int page = update[pageInd];
		for (vector<int> rule : rules)
		{
			if (rule[0] == page)
			{
				for (size_t otherInd = 0; otherInd < pageInd; otherInd++)
				{
					if (update[otherInd] == rule[1])
					{
						return false;
					}
				}
			}
			else if (rule[1] == page)
			{
				for (size_t otherInd = pageInd + 1; otherInd < update.size(); otherInd++)
				{
					if (update[otherInd] == rule[0])
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

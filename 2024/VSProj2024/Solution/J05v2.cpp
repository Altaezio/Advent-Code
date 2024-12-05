#include <FileHandler.h>
#include <iostream>
#include <algorithm>
#include "J05.h"

using namespace std;

struct PagesComparator
{
	PagesComparator(vector<vector<int>>* rules) :rules(rules) {}
	vector<vector<int>>* rules;
	bool operator()(const int& a, const int& b) const
	{
		for (vector<int> rule : *rules)
		{
			if (rule[0] == a && rule[1] == b)
			{
				return true;
			}
		}
		return false;
	}
};

string sol05v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<vector<int>> orderingRules;
	bool pageOrdering = true;
	int sum = 0;
	vector<vector<int>> unorderedUpdates;
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
		if (!UpdateIsInOrder(orderingRules, update))
		{
			unorderedUpdates.push_back(update);
		}
	}

	for (vector<int> update : unorderedUpdates)
	{
		sort(update.begin(), update.end(), PagesComparator(&orderingRules));
		size_t middleInd = (update.size() - 1) / 2;
		sum += update[middleInd];
	}

	return to_string(sum);
}

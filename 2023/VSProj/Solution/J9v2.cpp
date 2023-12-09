#include <iostream>
#include <numeric>
#include "../FileHandler.h"
#include "J9.h"

using namespace std;

string sol9v2()
{
	vector<string> lines = getSolutionLines("J9");

	int sum = 0;
	for (string line : lines)
	{
		sum += previousValue(line);
	}
	return to_string(sum);
}

int previousValue(string line)
{
	vector<int> history = ExtractInt(line);
	vector<vector<int>> diffs{ history };
	while (accumulate(diffs.back().begin(), diffs.back().end(), 0) != 0)
	{
		diffs.push_back(diffVector(diffs.back()));
	}

	int nextValue = 0;
	for (size_t i = diffs.size() - 1; i > 0; i--)
	{

		nextValue = diffs[i - 1][0] - nextValue;
	}
	return nextValue;
}

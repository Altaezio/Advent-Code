#include <iostream>
#include <map>
#include "../FileHandler.h"
#include "J5.h"

using namespace std;

string sol5v2()
{
	vector<string> lines = getSolutionLines("J5");

	vector<long long> seeds = Extractll(lines[0].substr(6));
	vector<vector<long long>> seedsRange;

	for (size_t seedi = 0; seedi < seeds.size(); seedi += 2)
	{
		seedsRange.push_back(vector<long long> {seeds[seedi], seeds[seedi + 1]});
	}

	vector<vector<vector<long long>>> intervals(7);
	size_t currentInterval = 0;

	for (size_t lineIndex = 3; lineIndex < lines.size(); lineIndex++)
	{
		string line = lines[lineIndex];
		if (line.size() < 2)
		{
			currentInterval++;
			lineIndex++;
			continue;
		}

		intervals[currentInterval].push_back(Extractll(line));
	}

	long long lowestLocation = getValueIntervalRange(intervals, seedsRange);
	return to_string(lowestLocation);
}

long long getValueIntervalRange(std::vector<std::vector<std::vector<long long>>>& intervals, vector<vector<long long>> seeds)
{
	vector<vector<long long>> valuesLeft;
	vector<vector<long long>> valuesNext = seeds;
	for (size_t mapi = 0; mapi < intervals.size(); mapi++)
	{
		valuesLeft = valuesNext;
		valuesNext.clear();
		for (size_t sectionj = 0; sectionj < intervals[mapi].size(); sectionj++)
		{
			vector<long long> section = intervals[mapi][sectionj];
			// a to b map
			long long a = section[1];
			long long b = section[0];
			long long offset = section[2];
			size_t numberValuesToCheck = valuesLeft.size();
			for (size_t valuek = 0; valuek < numberValuesToCheck; valuek++)
			{
				long long startValue = valuesLeft[valuek][0];
				long long rangeValue = valuesLeft[valuek][1];
				/*if (value >= a && value < a + offset)
				{
					value = b + (value - a);
				}*/

				if (a + offset <= startValue || a >= startValue + rangeValue) // value outside section
				{
					continue;
				}
				long long startPos = max(startValue, a);
				long long endPos = min(startValue + rangeValue, a + offset) - 1;

				valuesNext.push_back(vector<long long> {b + (startPos - a), endPos - startPos + 1});
				valuesLeft.erase(valuesLeft.begin() + valuek);
				valuek--;
				numberValuesToCheck--;
				if (a - startValue > 0)
				{
					valuesLeft.push_back(vector<long long> {startValue, a - startValue});
				}
				if (startValue + rangeValue - (a + offset) > 0)
				{
					valuesLeft.push_back(vector<long long> {a + offset - 1, startValue + rangeValue - (a + offset)});
				}
			}
		}
		valuesNext.insert(valuesNext.end(), valuesLeft.begin(), valuesLeft.end());
	}
	long long lowest = valuesNext[0][0];
	for (vector<long long> value : valuesNext)
	{
		lowest = min(lowest, value[0]);
	}
	return lowest;
}

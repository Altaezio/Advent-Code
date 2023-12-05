#include <iostream>
#include <map>
#include "../FileHandler.h"
#include "J5.h"

using namespace std;

string sol5v1()
{
	vector<string> lines = getSolutionLines("J5");

	vector<long long> seeds = Extractll(lines[0].substr(6));

	vector<vector<vector<long long>>> intervals(7);
	size_t currentInterval = 0;

	for (size_t lineIndex = 3; lineIndex < lines.size(); lineIndex++)
	{
		string line = lines[lineIndex];
		if (line.size() < 2)
		{
			currentInterval++;
			lineIndex += 2;
			continue;
		}

		intervals[currentInterval].push_back(Extractll(line));
	}

	long long lowestLocation = -1;
	for (long long seed : seeds)
	{
		long long value = getValueInterval(intervals, seed);
		if (lowestLocation == -1) { lowestLocation = value; }
		lowestLocation = min(lowestLocation, value);
	}
	return to_string(lowestLocation);
}

long long getValueInterval(std::vector<std::vector<std::vector<long long>>>& intervals, long long value)
{
	for (size_t i = 0; i < intervals.size(); i++)
	{
		for (size_t j = 0; j < intervals[i].size(); j++)
		{
			vector<long long> section = intervals[i][j];
			// a to b map
			long long a = section[1];
			long long b = section[0];
			long long offset = section[2];
			if (value >= a && value < a + offset)
			{
				value = b + (value - a);
				break; // next map
			}
		}
	}
	return value;
}

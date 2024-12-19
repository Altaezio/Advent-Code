#include <FileHandler.h>
#include <iostream>
#include "J19.h"

using namespace std;

string sol19v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<string> v_towels = ExtractWithoutChar(lines[0], ',');
	set<string> towels(v_towels.begin(), v_towels.end());
	size_t sum = 0;
	for (size_t i = 2; i < lines.size(); i++)
	{
		cout << "\rLine " << i - 1 << "/" << lines.size() - 2;// << endl;
		vector<map<string, size_t>> possibleTowels(lines[i].size(), {});
		sum += CountPossiblePatterns(towels, lines[i], possibleTowels, 0);
	}
	cout << endl;
	return to_string(sum);
}

size_t CountPossiblePatterns(const set<string>& towels, const string& pattern, vector<map<string, size_t>>& alreadyVisited, size_t start)
{
	size_t sum = 0;
	for (const string& towel : towels)
	{
		if (alreadyVisited[start].contains(towel))
		{
			sum += alreadyVisited[start][towel];
			continue;
		}


		if (start + towel.size() > pattern.size())
		{
			continue;
		}

		size_t towelSum = 0;
		if (pattern.substr(start, towel.size()) == towel)
		{
			if (start + towel.size() == pattern.size())
			{
				towelSum = 1;
			}
			else
			{
				towelSum = CountPossiblePatterns(towels, pattern, alreadyVisited, start + towel.size());
			}
		}
		alreadyVisited[start][towel] = towelSum;
		sum += towelSum;
	}
	return sum;
}

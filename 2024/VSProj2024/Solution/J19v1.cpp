#include <FileHandler.h>
#include <iostream>
#include "J19.h"

using namespace std;

string sol19v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<string> v_towels = ExtractWithoutChar(lines[0], ',');
	set<string> towels(v_towels.begin(), v_towels.end());
	size_t sum = 0;
	vector<string> impossibles;
	for (size_t i = 2; i < lines.size(); i++)
	{
		vector<set<string>> possibleTowels(lines[i].size(), {}); // for each char in pattern, save the already computed towels
		vector<string> validTowels(lines[i].size(), {});
		cout << "\rLine " << i - 1 << "/" << lines.size() - 2;// << endl;
		//cout << lines[i] << endl;
		if (IsPatternPossible(towels, lines[i], possibleTowels, 0, validTowels))
		{
			sum++;
			/*for (size_t ind = 0; ind < lines[i].size();)
			{
				string& towel = validTowels[ind];
				cout << towel << ",";
				ind += towel.size();
			}
			cout << endl << endl;*/
		}
		else
		{
			impossibles.push_back(lines[i]);
			//cout << "Impossible" << endl;
		}
	}
	/*cout << endl << "Impossibles:" << endl;
	for (size_t i = 0; i < impossibles.size(); i++)
	{
		cout << impossibles[i] << endl;
	}*/
	cout << endl;
	return to_string(sum);
}

bool IsPatternPossible(const set<string>& towels, const string& pattern, vector<set<string>>& alreadyVisited, size_t start, vector<string>& validTowels)
{
	for (const string& towel : towels)
	{
		if (alreadyVisited[start].contains(towel))
		{
			continue;
		}

		alreadyVisited[start].insert(towel);

		if (start + towel.size() > pattern.size())
		{
			continue;
		}

		if (pattern.substr(start, towel.size()) == towel)
		{
			if (start + towel.size() == pattern.size() ||								// I validated a pattern at the very end
				IsPatternPossible(towels, pattern, alreadyVisited, start + towel.size(), validTowels))	// this towel allow to have a valid pattern
			{
				validTowels[start] = towel;
				return true;
			}
		}
	}
	return false;
}

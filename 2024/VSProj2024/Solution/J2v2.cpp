#include <FileHandler.h>
#include <iostream>
#include "J2.h"

using namespace std;

string sol02v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	int safeReports = 0;
	for (string line : lines)
	{
		vector<int> levels = ExtractInt(line);
		bool increasing = levels[0] < levels[levels.size() - 1];
		bool safe = true;
		size_t removed = -1;
		for (size_t ind = 0; ind < levels.size() - 1; ind++)
		{
			int level1 = levels[ind];
			int level2 = levels[ind + 1];

			if (removed == ind)
				continue;

			if (LevelChangeNotSafe(increasing, level1, level2))
			{
				if (removed < levels.size() && ind != removed)
				{
					safe = false;
					break;
				}


				if (ind > 0 && !LevelChangeNotSafe(increasing, levels[ind - 1], levels[ind + 1]))
				{
					removed = ind;
				}
				else if (ind < levels.size() - 2 && !LevelChangeNotSafe(increasing, levels[ind], levels[ind + 2]))
				{
					removed = ind + 1;
				}
				else if (ind == 0)
				{
					removed = 0;
				}
				else if (ind == levels.size() - 2)
				{
					removed = levels.size() - 2;
				}
				else
				{
					safe = false;
					break;
				}
			}
		}
		if (safe)
			safeReports++;
		cout << line << "  :  " << (safe ? "safe" : "not safe");
		if (safe && removed < levels.size())
			cout << " by removing: " << levels[removed];
		cout << endl;
	}
	return to_string(safeReports);
}
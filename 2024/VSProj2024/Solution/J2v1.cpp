#include <FileHandler.h>
#include <iostream>
#include "J2.h"

using namespace std;

string sol02v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	int safeReports = 0;
	for (string line : lines)
	{
		vector<int> levels = ExtractInt(line);
		bool increasing = levels[0] < levels[1];
		bool safe = true;
		for (size_t ind = 0; ind < levels.size() - 1; ind++)
		{
			int level1 = levels[ind];
			int level2 = levels[ind + 1];

			if (LevelChangeNotSafe(increasing, level1, level2))
			{
				safe = false;
				break;
			}
		}
		if (safe)
			safeReports++;
	}
	return to_string(safeReports);
}

bool LevelChangeNotSafe(bool increasing, int level1, int level2)
{
	return ((level1 == level2) || // not changing
		(increasing && level1 > level2) || // not increasing while it should
		(!increasing && level1 < level2) || // not decreasing while it should
		(abs(level1 - level2) > 3)); // too big diff
}
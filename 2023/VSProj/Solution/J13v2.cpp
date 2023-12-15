#include <iostream>
#include "../FileHandler.h"
#include "J13.h"

using namespace std;

string sol13v2()
{
	vector<string> lines = getSolutionLines("J13");

	vector<vector<string>> patterns = getPatterns(lines);

	int sum = 0;
	for (vector<string> pattern : patterns)
	{
		int patternValue = getPatternValueV2(pattern);
		sum += patternValue;
	}
	return to_string(sum);
}

int getPatternValueV2(vector<string>& pattern)
{
	size_t symmetryPosition = symetryV2(pattern, &countDiffVertical, pattern[0].size());
	if (symmetryPosition != string::npos)
	{
		return symmetryPosition + 1;
	}

	symmetryPosition = symetryV2(pattern, &countDiffHorizontal, pattern.size());
	return 100 * (symmetryPosition + 1);
}

size_t symetryV2(vector<string>& pattern, int (*countDiff)(vector<string>&, size_t, size_t), size_t highLimit)
{
	for (size_t i = 0; i < highLimit - 1; i++)
	{
		if (isSymetricFromIndex(pattern, i, countDiff, highLimit))
		{
			return i;
		}
	}

	return string::npos;
}

bool isSymetricFromIndex(vector<string>& pattern, size_t refIndex, int (*countDiff)(vector<string>&, size_t, size_t), size_t highLimit)
{
	size_t upperIndex = refIndex;
	size_t lowerIndex = refIndex + 1;
	bool hasOneError = false;

	while (lowerIndex < highLimit)
	{
		int count = countDiff(pattern, upperIndex, lowerIndex);
		if (count == 1)
		{
			if (hasOneError)
			{
				return false;
			}
			hasOneError = true;
		}
		else if (count > 1)
		{
			return false;
		}

		if (upperIndex == 0)
		{
			return hasOneError;
		}
		upperIndex--;
		lowerIndex++;
	}
	return hasOneError;
}

int countDiffVertical(vector<string>& pattern, size_t aIndex, size_t bIndex)
{
	int count = 0;
	for (size_t i = 0; i < pattern.size(); i++)
	{
		if (pattern[i][aIndex] != pattern[i][bIndex])
		{
			count++;
		}
	}
	return count;
}

int countDiffHorizontal(vector<string>& pattern, size_t aIndex, size_t bIndex)
{
	int count = 0;
	for (size_t i = 0; i < pattern[0].size(); i++)
	{
		if (pattern[aIndex][i] != pattern[bIndex][i])
		{
			count++;
		}
	}
	return count;
}

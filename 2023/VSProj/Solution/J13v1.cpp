#include <iostream>
#include "../FileHandler.h"
#include "J13.h"

using namespace std;

string sol13v1()
{
	vector<string> lines = getSolutionLines("J13");

	vector<vector<string>> patterns = getPatterns(lines);

	int sum = 0;
	for (vector<string> pattern : patterns)
	{
		sum += getPatternValue(pattern);
	}
	return to_string(sum);
}

vector<vector<string>> getPatterns(vector<string>& lines)
{
	vector<vector<string>> patterns(1);
	size_t currentPattern = 0;
	for (size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i].size() < 2)
		{
			patterns.push_back(vector<string>());
			currentPattern++;
			continue;
		}

		patterns[currentPattern].push_back(lines[i]);
	}
	return patterns;
}

int getPatternValue(vector<string>& pattern)
{
	size_t symmetryPosition = verticalSymmetry(pattern);
	if (symmetryPosition != string::npos)
	{
		return symmetryPosition + 1;
	}

	symmetryPosition = horizontalSymmetry(pattern);
	return 100 * (symmetryPosition + 1);
}

size_t verticalSymmetry(vector<string>& pattern)
{
	for (size_t i = 0; i < pattern[0].size() - 1; i++)
	{
		if (areColumnsEquals(pattern, i, i + 1) && isVerticalySymmetricFromIndex(pattern, i))
		{
			return i;
		}
	}

	return string::npos;
}

size_t horizontalSymmetry(vector<string>& pattern)
{
	for (size_t i = 0; i < pattern.size() - 1; i++)
	{
		if (pattern[i] == pattern[i + 1] && isHorizontalySymmetricFromIndex(pattern, i))
		{
			return i;
		}
	}

	return string::npos;
}

bool isVerticalySymmetricFromIndex(vector<string>& pattern, size_t refIndex)
{
	size_t upperIndex = refIndex;
	size_t lowerIndex = refIndex + 1;

	while (lowerIndex < pattern[0].size())
	{
		if (!areColumnsEquals(pattern, upperIndex, lowerIndex))
		{
			return false;
		}
		if (upperIndex == 0)
		{
			return true;
		}
		upperIndex--;
		lowerIndex++;
	}
	return true;
}

bool isHorizontalySymmetricFromIndex(vector<string>& pattern, size_t refIndex)
{
	size_t upperIndex = refIndex;
	size_t lowerIndex = refIndex + 1;

	while (lowerIndex < pattern.size())
	{
		if (pattern[upperIndex] != pattern[lowerIndex])
		{
			return false;
		}
		if (upperIndex == 0)
		{
			return true;
		}
		upperIndex--;
		lowerIndex++;
	}
	return true;
}

bool areColumnsEquals(vector<string>& pattern, size_t aIndex, size_t bIndex)
{
	for (size_t i = 0; i < pattern.size(); i++)
	{
		if (pattern[i][aIndex] != pattern[i][bIndex])
		{
			return false;
		}
	}
	return true;
}

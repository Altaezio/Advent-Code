#include <FileHandler.h>
#include <iostream>
#include "J10.h"

using namespace std;

string sol10v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	size_t sum = 0;
	for (size_t y = 0; y < lines.size(); y++)
	{
		string line = lines[y];
		for (size_t x = 0; x < line.size(); x++)
		{
			if (line[x] == '0')
			{
				sum += Find9_Rec(lines, { x,y });
			}
		}
	}
	return to_string(sum);
}

size_t Find9_Rec(vector<string>& lines, vector<size_t> start)
{
	if (lines[start[1]][start[0]] == '9')
	{
		return 1;
	}

	size_t sum = 0;
	for (vector<size_t> nPos : GetNeighbors(lines, start))
	{
		sum += Find9_Rec(lines, nPos);
	}
	return sum;
}

#include <FileHandler.h>
#include <iostream>
#include "J10.h"

using namespace std;

string sol10v1(string solutionFileName)
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
				set<vector<size_t>> found = FindUnique9_Rec(lines, { x,y });
				sum += found.size();
			}
		}
	}
	return to_string(sum);
}

vector<vector<size_t>> GetNeighbors(vector<string>& lines, vector<size_t> pos)
{
	vector<vector<size_t>> neighbors;
	char current = lines[pos[1]][pos[0]];
	if (pos[0] > 0)
	{
		vector<size_t> nPos = { pos[0] - 1, pos[1] };

		char n = lines[nPos[1]][nPos[0]];
		if (n == current + 1)
			neighbors.push_back(nPos);
	}
	if (pos[1] > 0)
	{
		vector<size_t> nPos = { pos[0], pos[1] - 1 };

		char n = lines[nPos[1]][nPos[0]];
		if (n == current + 1)
			neighbors.push_back(nPos);
	}
	if (pos[0] + 1 < lines[pos[1]].size())
	{
		vector<size_t> nPos = { pos[0] + 1, pos[1] };

		char n = lines[nPos[1]][nPos[0]];
		if (n == current + 1)
			neighbors.push_back(nPos);
	}
	if (pos[1] + 1 < lines.size())
	{
		vector<size_t> nPos = { pos[0], pos[1] + 1 };

		char n = lines[nPos[1]][nPos[0]];
		if (n == current + 1)
			neighbors.push_back(nPos);
	}
	return neighbors;
}

set<vector<size_t>> FindUnique9_Rec(vector<string>& lines, vector<size_t> start)
{
	set<vector<size_t>> found;
	if (lines[start[1]][start[0]] == '9')
	{
		found.insert(start);
		return found;
	}

	for (vector<size_t> nPos : GetNeighbors(lines, start))
	{
		set<vector<size_t>> fBis = FindUnique9_Rec(lines, nPos);
		found.insert(fBis.begin(), fBis.end());
	}
	return found;
}

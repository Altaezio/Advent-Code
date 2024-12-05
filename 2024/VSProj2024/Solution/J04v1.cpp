#include <FileHandler.h>
#include <iostream>
#include <numbers>
#include "J04.h"

using namespace std;

string sol04v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	int occurence = 0;
	for (size_t row = 0; row < lines.size(); row++)
	{
		string line = lines[row];
		for (size_t col = 0; col < line.size(); col++)
		{
			for (int xDir = -1; xDir <= 1; xDir++)
			{
				for (int yDir = -1; yDir <= 1; yDir++)
				{
					if (xDir == 0 && yDir == 0)
						continue;
					if (MatchWord(lines, row, col, xDir, yDir, "XMAS"))
						occurence++;
				}
			}
		}
	}
	return to_string(occurence);
}

bool MatchWord(vector<string>& lines, size_t startRow, size_t startCol, int xDir, int yDir, string wordToMatch)
{
	for (size_t step = 0; step < wordToMatch.size(); step++)
	{
		size_t row = startRow + step * yDir;
		size_t col = startCol + step * xDir;
		if (row >= lines.size() || col >= lines[row].size())
			return false;
		if (lines[row][col] != wordToMatch[step])
			return false;
	}
	return true;
}


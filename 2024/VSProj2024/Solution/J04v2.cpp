#include <FileHandler.h>
#include <iostream>
#include "J04.h"

using namespace std;

string sol04v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	int occurence = 0;
	for (size_t row = 0; row < lines.size(); row++)
	{
		string line = lines[row];
		for (size_t col = 0; col < line.size(); col++)
		{
			char a = line[col];
			if (a != 'A')
				continue;
			int nMatches = 0;
			for (int xDir = -1; xDir <= 1; xDir += 2)
			{
				for (int yDir = -1; yDir <= 1; yDir += 2)
				{
					if (MatchWord(lines, row - yDir, col - xDir, xDir, yDir, "MAS"))
						nMatches++;
				}
			}
			if (nMatches >= 2)
				occurence++;
		}
	}
	return to_string(occurence);
}

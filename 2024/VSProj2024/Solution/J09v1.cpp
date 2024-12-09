#include <FileHandler.h>
#include <iostream>
#include "J09.h"

using namespace std;

string sol09v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	size_t sum = 0;
	for (string line : lines)
	{
		size_t ind = 0;
		size_t beginBlockID = 0;
		size_t endBlockID = (line.size() - 1) / 2;
		size_t endBlockLeft = line[endBlockID * 2] - '0';
		for (size_t i = 0; i < line.size(); i += 2)
		{
			int block = line[i] - '0';
			for (size_t b = 0; b < block; b++)
			{
				sum += ind * beginBlockID;
				ind++;
				if (beginBlockID == endBlockID)
				{
					endBlockLeft--;
					if (endBlockLeft == 0)
					{
						break;
					}
				}
			}
			beginBlockID++;

			int space = line[i + 1] - '0';
			for (size_t s = 0; s < space && endBlockLeft > 0; s++)
			{
				sum += ind * endBlockID;
				ind++;
				endBlockLeft--;
				if (endBlockLeft == 0)
				{
					endBlockID--;
					endBlockLeft = line[endBlockID * 2] - '0';
				}
			}
			if (endBlockID < beginBlockID || (endBlockID == beginBlockID && endBlockLeft == 0))
			{
				break;
			}
		}
	}

	return to_string(sum);
}

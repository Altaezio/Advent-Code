#include <FileHandler.h>
#include <iostream>
#include <regex>
#include "J13.h"

using namespace std;

string sol13v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	size_t sum = 0;
	for (size_t lInd = 0; lInd < lines.size(); lInd += 4)
	{
		vector<size_t> A = ExtractullAmongOther(lines[lInd]);
		vector<size_t> B = ExtractullAmongOther(lines[lInd + 1]);
		vector<size_t> prize = ExtractullAmongOther(lines[lInd + 2]);


		size_t bestPressCost = 0;
		for (size_t a = 1; a <= 100; a++)
		{
			for (size_t b = 1; b <= 100; b++)
			{
				if (A[0] * a + B[0] * b != prize[0] || A[1] * a + B[1] * b != prize[1])
				{
					continue;
				}
				if (bestPressCost == 0 || bestPressCost > a * 3 + b)
				{
					bestPressCost = a * 3 + b;
				}
			}
		}
		if (bestPressCost != 0)
		{
			sum += bestPressCost;
		}
	}
	return to_string(sum);
}


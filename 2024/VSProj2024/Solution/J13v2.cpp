#include <FileHandler.h>
#include <iostream>
#include "J13.h"

using namespace std;
using ll = long long;

string sol13v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	size_t sum = 0;
	size_t prizeOffset = 10000000000000;
	for (size_t lInd = 0; lInd < lines.size(); lInd += 4)
	{
		vector<ll> A = ExtractllAmongOther(lines[lInd]);
		vector<ll> B = ExtractllAmongOther(lines[lInd + 1]);
		vector<ll> prize = ExtractllAmongOther(lines[lInd + 2]);
		prize[0] += prizeOffset;
		prize[1] += prizeOffset;

		double x = (double)(prize[0] - ((double)(prize[1] * B[0]) / B[1])) / (A[0] - ((double)(A[1] * B[0]) / B[1]));
		double y = (double)(prize[1] - x * A[1]) / B[1];
		double roundX = round(x);
		double roundY = round(y);
		if (x > 0 && y > 0 &&
			roundX * A[0] + roundY * B[0] == prize[0] &&
			roundX * A[1] + roundY * B[1] == prize[1])
		{
			sum += roundX * 3 + roundY;
		}
	}
	return to_string(sum);
}

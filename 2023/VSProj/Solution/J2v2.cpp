#include <iostream>
#include "../FileHandler.h"
#include "J2.h"

using namespace std;

string sol2v2()
{
	vector<string> lines = getSolutionLines("J2");

	int sumPower = 0;

	for (string line : lines)
	{
		vector<subset> game = extractGame(line);
		subset minSubset = getMinSubset(game);
		int power = minSubset.red * minSubset.green * minSubset.blue;
		sumPower += power;
	}

	return to_string(sumPower);
}

subset getMinSubset(vector<subset> game)
{
	if(game.size()<= 0)
	{
		return subset(0, 0, 0);
	}

	subset minimumSubset = game[0];
	for (subset subsetTest : game)
	{
		minimumSubset = maxSubset(minimumSubset, subsetTest);
	}
	return minimumSubset;
}

subset maxSubset(subset a, subset b)
{
	return subset(max(a.red, b.red), max(a.green, b.green), max(a.blue, b.blue));
}

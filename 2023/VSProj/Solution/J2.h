#pragma once
#include <vector>

std::string sol2v1();
std::string sol2v2();

struct subset
{
	int red;
	int green;
	int blue;

	subset(int red, int green, int blue) : red(red), green(green), blue(blue) {}
};

std::vector<subset> extractGame(std::string line);

subset extractSubset(std::string stringSubset);

bool subsetAinB(subset a, subset b);

subset getMinSubset(std::vector<subset> game);

subset maxSubset(subset a, subset b);

#include <FileHandler.h>
#include <iostream>
#include "J11.h"

using namespace std;
using ull = unsigned long long;

string sol11v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	size_t maxDepth = 75;
	size_t nStones = 0;
	for (string line : lines)
	{
		vector<ull> stones = Extractull(line);
		map<ull, vector<long long>> tree;
		for (ull startStone : stones)
		{
			nStones += SplitStone_Rec(startStone, tree, maxDepth);
		}
	}
	return to_string(nStones);
}

size_t SplitStone_Rec(ull stone, map<ull, vector<long long>>& tree, size_t depthLeft)
{
	if (depthLeft == 0)
	{
		if (tree[stone].size() == 0)
		{
			tree[stone].push_back(1);
		}
		else
		{
			tree[stone][0] = 1;
		}
		return 1;
	}

	if (tree.find(stone) != tree.end())
	{
		if (depthLeft < tree[stone].size() && tree[stone][depthLeft] > 0)
		{
			return tree[stone][depthLeft];
		}
	}

	size_t subStones = 0;
	size_t stoneSize = floor(log10(stone) + 1);
	if (stone == 0)
	{
		subStones = SplitStone_Rec(1, tree, depthLeft - 1);
	}
	else if (stoneSize % 2 == 0)
	{
		size_t total = 0;
		ull sub2 = stone / (pow(10, stoneSize / 2));
		ull sub1 = stone - sub2 * (pow(10, stoneSize / 2));
		total += SplitStone_Rec(sub1, tree, depthLeft - 1);
		total += SplitStone_Rec(sub2, tree, depthLeft - 1);
		subStones = total;
	}
	else
	{
		// odd number of digits
		subStones = SplitStone_Rec(stone * 2024, tree, depthLeft - 1);
	}

	if (tree.find(stone) == tree.end())
	{
		vector<long long> newVec(depthLeft + 1, -1);
		newVec[depthLeft] = subStones;
		tree[stone] = newVec;
	}
	else
	{
		if (depthLeft >= tree[stone].size())
		{
			tree[stone].resize(depthLeft + 1, -1);
		}
		tree[stone][depthLeft] = subStones;
	}
	return subStones;
}

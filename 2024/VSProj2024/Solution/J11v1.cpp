#include <FileHandler.h>
#include <iostream>
#include "J11.h"

using namespace std;
using ull = unsigned long long;

string sol11v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	size_t nStones = 0;
	for (string line : lines)
	{
		map<ull, vector<long long>> tree;
		vector<ull> stones = Extractull(line);
		for (ull stone : stones)
		{
			nStones += SplitStone_Rec(stone, tree, 25);
		}
		/* slow methode
		vector<string> stones = Extract(line);
		for (size_t blink = 0; blink < 25; blink++)
		{
			stones = SplitStones(stones);
		}
		nStones = stones.size();
		*/
	}
	return to_string(nStones);
}

vector<string> SplitStones(vector<string>& stones)
{
	vector<string> newStones;
	for (string stone : stones)
	{
		vector<string> splitted = SplitOneStone(stone);
		newStones.insert(newStones.end(), splitted.begin(), splitted.end());
	}
	return newStones;
}

vector<string> SplitOneStone(string stoneStr)
{
	if (stoneStr.size() == 1 && stoneStr[0] == '0')
	{
		return { "1" };
	}

	if (stoneStr.size() % 2 == 0)
	{
		vector<string> stoneOut;
		ull sub1 = stoull(stoneStr.substr(0, stoneStr.size() / 2));
		stoneOut.push_back(to_string(sub1));
		ull sub2 = stoull(stoneStr.substr(stoneStr.size() / 2, stoneStr.size() / 2));
		stoneOut.push_back(to_string(sub2));
		return stoneOut;
	}

	// odd number of digits
	ull stone = stoull(stoneStr);
	return { to_string(stone * 2024) };
}

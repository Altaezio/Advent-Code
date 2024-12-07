#include <FileHandler.h>
#include <iostream>
#include "J07.h"

using namespace std;
using ull = unsigned long long;

string sol07v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<function<ull(ull, ull)>> operations;
	operations.push_back(multiplies<ull>());
	operations.push_back(plus<ull>());
	operations.push_back(Concatenation);
	ull sum = 0;
	for (string line : lines)
	{
		size_t delimiter = line.find(':');
		string targetSubStr = line.substr(0, delimiter);
		ull targetNum = stoull(targetSubStr);
		string valuesSubStr = line.substr(delimiter + 1);
		vector<int> operatedValues = ExtractInt(valuesSubStr);
		if (CanBeEqual(operations, operatedValues, targetNum))
		{
			sum += targetNum;
		}
	}
	return to_string(sum);
}

ull Concatenation(ull a, ull b)
{
	string aStr = to_string(a);
	string bStr = to_string(b);
	aStr.append(bStr);
	return stoull(aStr);
}

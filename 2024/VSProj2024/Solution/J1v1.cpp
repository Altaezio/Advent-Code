#include <FileHandler.h>
#include <iostream>
#include <algorithm>
#include "J1.h"

using namespace std;

string sol01v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<int> a;
	vector<int> b;
	for (string line : lines)
	{
		vector<int> ids = ExtractInt(line);
		a.push_back(ids[0]);
		b.push_back(ids[1]);
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int sumDist = 0;
	for (int i = 0; i < a.size(); i++)
	{
		sumDist += abs(a[i] - b[i]);
	}
	return to_string(sumDist);
}
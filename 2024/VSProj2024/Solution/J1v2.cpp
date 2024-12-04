#include <FileHandler.h>
#include <iostream>
#include <algorithm>
#include "J1.h"

using namespace std;

string sol01v2(string solutionFileName)
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
	int similarity = 0;
	for (int leftID : a)
	{
		similarity += leftID * count(b.begin(), b.end(), leftID);
	}
	return to_string(similarity);
}
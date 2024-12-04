#include <FileHandler.h>
#include <iostream>
#include <regex>
#include "J3.h"

using namespace std;

string sol03v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	int sum = 0;
	bool enable = true;
	for (string line : lines)
	{
		regex mul(R"((mul\([\d]+,[\d]+\))|(do\(\))|(don\'t\(\)))");
		auto mulBegin = sregex_iterator(line.begin(), line.end(), mul);
		auto mulEnd = sregex_iterator();
		for (sregex_iterator i = mulBegin; i != mulEnd; i++)
		{
			smatch match = *i;
			string matchStr = match.str();
			if (matchStr.compare("do()") == 0)
			{
				enable = true;
				continue;
			}
			if (matchStr.compare("don't()") == 0)
				enable = false;
			if (!enable)
				continue;
			regex num(R"([\d]+)");
			auto numBegin = sregex_iterator(matchStr.begin(), matchStr.end(), num);
			auto numEnd = sregex_iterator();
			int m = 1;
			for (sregex_iterator j = numBegin; j != numEnd; j++)
			{
				string numStr = (*j).str();
				m *= stoi(numStr);
			}
			sum += m;
		}
	}
	return to_string(sum);
}
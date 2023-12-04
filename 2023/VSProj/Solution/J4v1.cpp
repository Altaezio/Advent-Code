#include <iostream>
#include <sstream>
#include "../FileHandler.h"
#include "J4.h"

using namespace std;

string sol4v1()
{
	vector<string> lines = getSolutionLines("J4");

	int sum = 0;

	for (string line : lines)
	{
		size_t beginWinning = line.find_first_of(":") + 1;
		size_t bar = line.find_first_of("|");
		string winning = line.substr(beginWinning, (bar - 1) - beginWinning);
		string having = line.substr(bar + 1);
		vector<int> winningNumbers = ExtractInt(winning);
		vector<int> havingNumbers = ExtractInt(having);

		int sumCard = 0;
		for (int number : havingNumbers)
		{
			if (find(winningNumbers.begin(), winningNumbers.end(), number) != winningNumbers.end())
			{
				if(sumCard == 0)
				{
					sumCard = 1;
				}
				else
				{
					sumCard *= 2;
				}
			}
		}
		sum += sumCard;
	}
	return to_string(sum);
}

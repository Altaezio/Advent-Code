#include <iostream>
#include <sstream>
#include <numeric>
#include "../FileHandler.h"
#include "J4.h"

using namespace std;

string sol4v2()
{
	vector<string> lines = getSolutionLines("J4");

	vector<int> numberOfCards(lines.size(), 1);

	for (size_t i = 0; i < lines.size(); i++)
	{
		string line = lines[i];
		size_t beginWinning = line.find_first_of(":") + 1;
		size_t bar = line.find_first_of("|");
		string winning = line.substr(beginWinning, (bar - 1) - beginWinning);
		string having = line.substr(bar + 1);
		vector<int> winningNumbers = ExtractInt(winning);
		vector<int> havingNumbers = ExtractInt(having);

		size_t numberOfMatching = 0;
		for (int number : havingNumbers)
		{
			if (find(winningNumbers.begin(), winningNumbers.end(), number) != winningNumbers.end())
			{
				numberOfMatching++;
			}
		}
		for (size_t j = 0; j < numberOfMatching; j++)
		{
			numberOfCards[i + j + 1] += 1 * numberOfCards[i];
		}
	}
	return to_string(accumulate(numberOfCards.begin(), numberOfCards.end(), 0));
}
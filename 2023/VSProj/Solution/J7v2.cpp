#include <iostream>
#include <map>
#include <algorithm>
#include "../FileHandler.h"
#include "J5.h"
#include "J7.h"

using namespace std;

string sol7v2()
{
	vector<string> lines = getSolutionLines("J7"); // to high

	vector<tuple<string, int, int>> bidHandValue;

	for (string line : lines)
	{
		string hand = line.substr(0, 5);
		int bid = stoi(line.substr(5));
		int handValue = evaluateHandJoker(hand);
		bidHandValue.push_back(make_tuple(hand, bid, handValue));
	}
	sort(bidHandValue.begin(), bidHandValue.end(), compHand);
	int sum = 0;
	for (size_t i = 0; i < bidHandValue.size(); i++)
	{
		sum += get<1>(bidHandValue[i]) * (i + 1);
	}
	return to_string(sum);
}

int evaluateHandJoker(string hand)
{
	vector<int> occurenceCards(13, 0);
	for (char& c : hand)
	{
			occurenceCards[cardToIntJoker(c) - 1] += 1;
	}

	int numberJs = occurenceCards[cardToIntJoker('J') - 1];
	occurenceCards[cardToIntJoker('J') - 1] = 0;
	vector<int>::iterator maxElem = max_element(occurenceCards.begin(), occurenceCards.end());

	*maxElem = *maxElem + numberJs;

	int value = 0;
	for (int occurence : occurenceCards)
	{
		if (occurence == 2)
		{
			value++;
		}
		else if (occurence == 3)
		{
			value += 3;
		}
		else if (occurence >= 4)
		{
			value += occurence + 1;
		}
	}
	return value;
}

int cardToIntJoker(char c)
{
	switch (c)
	{
	case 'A':
		return 13;
	case 'K':
		return 12;
	case 'Q':
		return 11;
	case 'J':
		return 1;
	case 'T':
		return 10;
	default:
		return c - '0';
	}
}

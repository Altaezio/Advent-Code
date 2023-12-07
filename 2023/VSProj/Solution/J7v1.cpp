#include <iostream>
#include <map>
#include <algorithm>
#include "../FileHandler.h"
#include "J5.h"
#include "J7.h"

using namespace std;

string sol7v1()
{
	vector<string> lines = getSolutionLines("J7");

	vector<tuple<string, int, int>> bidHandValue;

	for (string line : lines)
	{
		string hand = line.substr(0, 5);
		int bid = stoi(line.substr(5));
		int handValue = evaluateHand(hand);
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

int evaluateHand(string hand)
{
	map<char, int> occurenceCards;
	for (char& c : hand)
	{
		if (occurenceCards.find(c) == occurenceCards.end())
		{
			occurenceCards[c] = 1;
		}
		else
		{
			occurenceCards[c] += 1;
		}
	}

	int value = 0;
	for (auto const& [card, occurence] : occurenceCards)
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

bool compHand(tuple<string, int, int> a, tuple<string, int, int> b)
{
	int aHandValue = get<2>(a);
	int bHandValue = get<2>(b);
	if (aHandValue != bHandValue)
	{
		return aHandValue < bHandValue;
	}

	for (size_t ci = 0; ci < 5; ci++)
	{
		char& aCard = get<0>(a)[ci];
		char& bCard = get<0>(b)[ci];
		int aCInt = cardToInt(aCard);
		int bCInt = cardToInt(bCard);
		if (aCInt != bCInt)
		{
			return aCInt < bCInt;
		}
	}
	return true; // a == b so a first shoudln't happen I guess
}

int cardToInt(char& c)
{
	switch (c)
	{
	case 'A':
		return 14;
	case 'K':
		return 13;
	case 'Q':
		return 12;
	case 'J':
		return 11;
	case 'T':
		return 10;
	default:
		return c - '0';
	}
}

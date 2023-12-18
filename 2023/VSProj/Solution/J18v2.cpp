#include <iostream>
#include <map>
#include "../FileHandler.h"
#include "J18.h"

using namespace std;

string sol18v2()
{
	vector<string> lines = getSolutionLines("test");
	pair<long, long> currentCoord, previousCoord;
	currentCoord = make_pair(0, 0);
	previousCoord = currentCoord;
	long area = 0;
	long border = 0;

	for (string line : lines)
	{
		vector<string> extracted = Extract(line);
		string hex = extracted[2];
		string translatedString;
		long iterations = stol(hex.substr(2, 5), nullptr, 16);

		pair<long, long> directionPair = make_pair(0, 0);
		if (hex[7] == '2') // L
		{
			directionPair.second = -1 * iterations;
		}
		else if (hex[7] == '0') // R
		{
			directionPair.second = 1 * iterations;
		}
		else if (hex[7] == '3') // U
		{
			directionPair.first = -1 * iterations;
		}
		else if (hex[7] == '1') // D
		{
			directionPair.first = 1 * iterations;
		}

		previousCoord = currentCoord;
		currentCoord = make_pair(currentCoord.first + directionPair.first, currentCoord.second + directionPair.second);
		area += previousCoord.second * currentCoord.first - previousCoord.first * currentCoord.second;
		border += iterations;
	}
	area = abs(area) / 2;
	long inside = area - border / 2 + 1;
	return to_string(inside + border);
}

vector<string> translateLines(vector<string> lines)
{
	vector<string> translated;
	for (string line : lines)
	{
		vector<string> extracted = Extract(line);
		string hex = extracted[2];
		string translatedString;
		unsigned distance = stoul(hex.substr(2, 5), nullptr, 16);
		if (hex[7] == '0')
		{
			translatedString.append("R");
		}
		else if (hex[7] == '1')
		{
			translatedString.append("D");
		}
		else if (hex[7] == '2')
		{
			translatedString.append("L");
		}
		else if (hex[7] == '3')
		{
			translatedString.append("U");
		}
		translatedString.append(" " + to_string(distance));
		translated.push_back(translatedString);
	}
	return translated;
}


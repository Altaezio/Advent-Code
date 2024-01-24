#include <iostream>
#include <algorithm>
#include "../FileHandler.h"
#include "J14.h"

using namespace std;

string sol14v2()
{
	vector<string> lines = getSolutionLines("J14");

	int load = 0;

	vector<pair<size_t, size_t>> rocks = getRocks(lines);
	vector<vector<pair<size_t, size_t>>> patterns;
	vector<int> patternValues;

	vector< pair<int, int>> directions{ make_pair(-1,0),make_pair(0,-1), make_pair(1,0), make_pair(0,1) };

	const size_t cycleToDo = 1000000000;
	for (size_t cycle = 0; cycle < cycleToDo; cycle++)
	{
		int tiltValue = 0;
		for (size_t tilt = 0; tilt < 4; tilt++)
		{
			pair<int, int> direction = directions[tilt];

			sortRocks(rocks, tilt);

			tiltValue = tiltInAnyDirection(lines, rocks, direction);
		}

		auto patternIt = find(patterns.begin(), patterns.end(), rocks);
		if (patternIt != patterns.end())
		{
			size_t matchingElemIndex = patternIt - patterns.begin();
			size_t lastElemIndex = matchingElemIndex + ((cycleToDo - (cycle + 1)) % (patterns.size() - matchingElemIndex));
			load = patternValues[lastElemIndex];
			return to_string(load);
		}

		patterns.push_back(rocks);
		patternValues.push_back(tiltValue);

	}
	return "Made all the way through, might have been long. Answer is : " + to_string(patternValues.back());
}


vector<pair<size_t, size_t>> getRocks(const vector<string>& lines)
{
	vector<pair<size_t, size_t>> rocks;
	for (size_t lineIndex = 0; lineIndex < lines.size(); lineIndex++)
	{
		string line = lines[lineIndex];
		for (size_t charIndex = 0; charIndex < line.size(); charIndex++)
		{
			char c = line[charIndex];
			if (c == 'O')
			{
				rocks.push_back(make_pair(lineIndex, charIndex));
			}
		}
	}
	return rocks;
}

void sortRocks(vector<pair<size_t, size_t>>& rocks, const int tilt)
{
	switch (tilt)
	{
	case 0:
		sort(rocks.begin(), rocks.end(), [](pair<size_t, size_t> a, pair<size_t, size_t> b) {return a.first < b.first || (a.first == b.first && a.second < b.second); });
		break;
	case 1:
		sort(rocks.begin(), rocks.end(), [](pair<size_t, size_t> a, pair<size_t, size_t> b) {return a.second < b.second || (a.first == b.first && b.first < a.first); });
		break;
	case 2:
		sort(rocks.begin(), rocks.end(), [](pair<size_t, size_t> a, pair<size_t, size_t> b) {return b.first < a.first || (a.first == b.first && b.second < a.second); });
		break;
	case 3:
		sort(rocks.begin(), rocks.end(), [](pair<size_t, size_t> a, pair<size_t, size_t> b) {return b.second < a.second || (a.first == b.first && b.first < a.first); });
		break;
	}
}

int tiltInAnyDirection(vector<string>& lines, vector<pair<size_t, size_t>>& rocks, const std::pair<int, int> direction)
{
	int tiltValue = 0;
	for (size_t rockIndex = 0; rockIndex < rocks.size(); rockIndex++)
	{
		pair<size_t, size_t> rock = rocks[rockIndex];
		pair<size_t, size_t> firstEmpty = findFirstEmpty(lines, rock, direction);
		if (firstEmpty.first != rock.first || firstEmpty.second != rock.second)
		{
			lines[firstEmpty.first][firstEmpty.second] = 'O';
			lines[rock.first][rock.second] = '.';
			rocks[rockIndex] = firstEmpty;
		}
		tiltValue += lines.size() - firstEmpty.first;
	}
	return tiltValue;
}

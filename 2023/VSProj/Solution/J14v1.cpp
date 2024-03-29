#include <iostream>
#include "../FileHandler.h"
#include "J14.h"

using namespace std;

string sol14v1()
{
	vector<string> lines = getSolutionLines("J14");

	int load = 0;

	pair<int, int> direction(-1, 0);
	load += tiltInDirection(lines, direction);
	coutList(lines);
	return to_string(load);
}

int tiltInDirection(std::vector<std::string>& lines, const std::pair<int, int> direction)
{
	int load = 0;
	for (size_t lineIndex = 0; lineIndex < lines.size(); lineIndex++)
	{
		string line = lines[lineIndex];
		for (size_t charIndex = 0; charIndex < line.size(); charIndex++)
		{
			char c = line[charIndex];
			if (c == 'O')
			{
				pair<size_t, size_t> firstEmpty = findFirstEmpty(lines, make_pair(lineIndex, charIndex), direction);
				if (firstEmpty.first != lineIndex || firstEmpty.second != charIndex)
				{
					lines[firstEmpty.first][firstEmpty.second] = 'O';
					lines[lineIndex][charIndex] = '.';
				}
				load += lines.size() - firstEmpty.first;
			}
		}
	}
	return load;
}

pair<size_t, size_t> findFirstEmpty(const vector<string>& lines, pair<size_t, size_t> start, pair<int, int> direction)
{
	pair<size_t, size_t> testedPosition = start;

	while (get<0>(testedPosition) + get<0>(direction) < lines.size() && get<1>(testedPosition) + get<1>(direction) < lines[0].size())
	{
		pair<size_t, size_t> nextPosition = testedPosition;
		nextPosition.first += get<0>(direction);
		nextPosition.second += get<1>(direction);
		if (lines[nextPosition.first][nextPosition.second] != '.')
		{
			return testedPosition;
		}
		testedPosition = nextPosition;
	}
	return testedPosition;
}

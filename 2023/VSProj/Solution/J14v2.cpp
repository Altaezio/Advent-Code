#include <iostream>
#include <algorithm>
#include "../FileHandler.h"
#include "J14.h"

using namespace std;

string sol14v2()
{
	vector<string> lines = getSolutionLines("test");

	int load = 0;

	vector<pair<size_t, size_t>> rocks;
	vector<int> patternValue;
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

	vector< pair<int, int>> directions{ make_pair(-1,0),make_pair(0,-1), make_pair(1,0), make_pair(0,1) };

	const size_t cycleToDo = 1000000000;
	for (size_t cycle = 0; cycle < cycleToDo; cycle++)
	{
		for (size_t tilt = 0; tilt < 4; tilt++)
		{
			pair<int, int> direction = directions[tilt];

			switch (tilt)
			{
			case 0:
				sort(rocks.begin(), rocks.end(), [](pair<size_t, size_t> a, pair<size_t, size_t> b) {return a.first < b.first; });
				break;
			case 1:
				sort(rocks.begin(), rocks.end(), [](pair<size_t, size_t> a, pair<size_t, size_t> b) {return a.second < b.second; });
				break;
			case 2:
				sort(rocks.begin(), rocks.end(), [](pair<size_t, size_t> a, pair<size_t, size_t> b) {return b.first < a.first; });
				break;
			case 3:
				sort(rocks.begin(), rocks.end(), [](pair<size_t, size_t> a, pair<size_t, size_t> b) {return b.second < a.second; });
				break;
			}

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
			// TODO
			patternValue.push_back(tiltValue);
			load += tiltValue;
		}
	}
	return to_string(load);
}

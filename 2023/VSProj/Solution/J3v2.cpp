#include <iostream>
#include <map>
#include "../FileHandler.h"
#include "J3.h"

using namespace std;

string sol3v2()
{
	vector<string> lines = getSolutionLines("J3");
	vector<string> debugLines{ string() };

	int sum = 0;

	map<tuple<size_t, size_t>, vector<int>> gearRatio;

	size_t currentColumn = 0;
	size_t currentLine = 0;
	while (true)
	{
		if (currentColumn >= lines[0].size()) // end of a line
		{
			currentLine++;
			if (currentLine >= lines.size()) // end of the table
			{
				coutList(debugLines);
				return to_string(sum);
			}
			debugLines.push_back(string());
			currentColumn = 0;
		}

		string line = lines[currentLine];

		if (!isdigit(line[currentColumn])) // NaN
		{
			debugLines[currentLine].push_back(line[currentColumn]);
			currentColumn++;
			continue;
		}

		string subLine = line.substr(currentColumn);
		size_t lengthNumber = 0;
		int partNumber = stoi(subLine, &lengthNumber);
		tuple<size_t, size_t> gearPosition;
		if (!getGearNeighbour(lines, currentLine, currentColumn, currentColumn + lengthNumber, gearPosition))
		{
			debugLines[currentLine].append(string(lengthNumber, 'X'));
		}
		else
		{
			debugLines[currentLine].append(to_string(partNumber));
			auto search = gearRatio.find(gearPosition);
			if (search != gearRatio.end())
			{
				cout << "(" << get<0>(gearPosition) << "," << get<1>(gearPosition) << ") : ";
				cout << search->second[0] << "*" << partNumber << endl;
				sum += search->second[0] * partNumber;
			}
			else
			{
				gearRatio[gearPosition] = vector<int>{ partNumber };
			}
		}

		currentColumn += lengthNumber;
	}
	return "error";
}

bool getGearNeighbour(vector<string> lines, size_t lineIndex, size_t begin, size_t end, tuple<size_t, size_t>& outGearPosition)
{
	size_t lowerEnd = 0uLL;
	if (begin > 0)
	{
		if (lines[lineIndex][begin - 1] == '*')
		{
			outGearPosition = tuple<size_t, size_t>{ lineIndex, begin - 1 };
			return true;
		}
		lowerEnd = begin - 1;
	}
	size_t higherEnd = end - lowerEnd;
	if (end + 1 < lines[0].size())
	{
		if (lines[lineIndex][end] == '*')
		{
			outGearPosition = tuple<size_t, size_t>{ lineIndex, end };
			return true;
		}
		higherEnd++;
	}

	if (lineIndex > 0)
	{
		string substr = lines[lineIndex - 1].substr(lowerEnd, higherEnd);
		size_t starPosition = substr.find_first_of("*");
		if (starPosition != string::npos)
		{
			outGearPosition = tuple<size_t, size_t>{ lineIndex - 1, lowerEnd + starPosition };
			return true;
		}
	}
	if (lineIndex + 1 < lines.size())
	{
		string substr = lines[lineIndex + 1].substr(lowerEnd, higherEnd);
		size_t starPosition = substr.find_first_of("*");
		if (starPosition != string::npos)
		{
			outGearPosition = tuple<size_t, size_t>{ lineIndex + 1, lowerEnd + starPosition };
			return true;
		}
	}

	return false;
}

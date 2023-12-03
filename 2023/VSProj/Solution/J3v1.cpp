#include <iostream>
#include "../FileHandler.h"
#include "J2.h"
#include "J3.h"

using namespace std;

string sol3v1()
{
	vector<string> lines = getSolutionLines("J3");
	vector<string> debugLines{ string() };

	int sum = 0;

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
		if (!oneNeighbourIsSymbol(lines, currentLine, currentColumn, currentColumn + lengthNumber))
		{
			debugLines[currentLine].append(string(lengthNumber, 'X'));
		}
		else
		{
			debugLines[currentLine].append(to_string(partNumber));
			sum += partNumber;
		}

		currentColumn += lengthNumber;
	}
	return "error";
}

bool oneNeighbourIsSymbol(std::vector<std::string> lines, size_t lineIndex, size_t begin, size_t end)
{
	size_t lowerEnd = 0uLL;
	if (begin > 0)
	{
		if (lines[lineIndex][begin - 1] != '.')
		{
			return true;
		}
		lowerEnd = begin - 1;
	}
	size_t higherEnd = end - lowerEnd;
	if (end + 1 < lines[0].size())
	{
		if (lines[lineIndex][end] != '.')
		{
			return true;
		}
		higherEnd++;
	}

	if (lineIndex > 0)
	{
		string substr = lines[lineIndex - 1].substr(lowerEnd, higherEnd);
		if (substr.find_first_not_of(".123456789") != string::npos)
		{
			return true;
		}
	}
	if (lineIndex + 1 < lines.size())
	{
		string substr = lines[lineIndex + 1].substr(lowerEnd, higherEnd);
		if (substr.find_first_not_of(".123456789") !=  string::npos)
		{
			return true;
		}
	}

	return false;
}

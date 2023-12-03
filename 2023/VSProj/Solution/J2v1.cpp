#include <iostream>
#include "../FileHandler.h"
#include "J2.h"

using namespace std;

string sol2v1()
{
	vector<string> lines = getSolutionLines("J2");

	subset possibleSubset(12, 13, 14);

	int sumID = 0;

	for (int i = 0; i < lines.size(); i++)
	{
		vector<subset> game = extractGame(lines[i]);
		sumID += i + 1;
		for (subset subsetTest : game)
		{
			if (!subsetAinB(subsetTest, possibleSubset))
			{
				cout << "Not good : ";
				cout << subsetTest.red << " red, ";
				cout << subsetTest.green << " green, ";
				cout << subsetTest.blue << " blue";
				cout << endl;
				sumID -= i + 1;
				break;
			}
			cout << "Good : ";
			cout << subsetTest.red << " red, ";
			cout << subsetTest.green << " green, ";
			cout << subsetTest.blue << " blue";
			cout << endl;
		}
	}
	return to_string(sumID);
}

vector<subset> extractGame(string line)
{
	vector<subset> extractedGame;
	string subLine = line;
	size_t lastPosition = line.find(";");
	while (lastPosition != string::npos)
	{
		extractedGame.push_back(extractSubset(subLine.substr(0, lastPosition)));
		subLine = subLine.substr(lastPosition + 1);
		lastPosition = subLine.find(";");
	}
	extractedGame.push_back(extractSubset(subLine.substr(lastPosition + 1)));
	return extractedGame;
}

subset extractSubset(std::string stringSubset)
{
	subset extractedSubset(0, 0, 0);
	size_t redPosition = stringSubset.find("red") - 3;
	if (redPosition < stringSubset.size())
	{
		extractedSubset.red = stoi(stringSubset.substr(redPosition));
	}
	size_t greenPosition = stringSubset.find("green") - 3;
	if (greenPosition < stringSubset.size())
	{
		extractedSubset.green = stoi(stringSubset.substr(greenPosition));
	}
	size_t bluePosition = stringSubset.find("blue") - 3;
	if (bluePosition < stringSubset.size())
	{
		extractedSubset.blue = stoi(stringSubset.substr(bluePosition));
	}
	return extractedSubset;
}

bool subsetAinB(subset a, subset b)
{
	return a.red <= b.red && a.green <= b.green && a.blue <= b.blue;
}

#include <FileHandler.h>
#include <iostream>
#include <set>
#include "J08.h"

using namespace std;

string sol08v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	map<char, vector<vector<int>>> antennaPos = GetAntennaPositions(lines);

	set<vector<int>> uniqueAntinodes;
	for (auto it = antennaPos.begin(); it != antennaPos.end(); it++)
	{
		char c = it->first;
		vector<vector<int>> positions = it->second;
		for (size_t i = 0; i < positions.size() - 1; i++)
		{
			for (size_t j = i + 1; j < positions.size(); j++)
			{
				int k = 1;
				while (true)
				{
					vector<int> antinodeIJ;
					antinodeIJ.push_back(k * (positions[j][0] - positions[i][0]) + positions[i][0]);
					antinodeIJ.push_back(k * (positions[j][1] - positions[i][1]) + positions[i][1]);
					if (antinodeIJ[0] >= 0 && antinodeIJ[0] < lines[0].size() &&
						antinodeIJ[1] >= 0 && antinodeIJ[1] < lines.size())
					{
						uniqueAntinodes.insert(antinodeIJ);
						k++;
					}
					else
					{
						break;
					}
				}
				k = 1;
				while (true)
				{
					vector<int> antinodeJI;
					antinodeJI.push_back(k * (positions[i][0] - positions[j][0]) + positions[j][0]);
					antinodeJI.push_back(k * (positions[i][1] - positions[j][1]) + positions[j][1]);
					if (antinodeJI[0] >= 0 && antinodeJI[0] < lines[0].size() &&
						antinodeJI[1] >= 0 && antinodeJI[1] < lines.size())
					{
						uniqueAntinodes.insert(antinodeJI);
						k++;
					}
					else
					{
						break;
					}
				}
			}
		}
	}

	if (solutionFileName == "test")
	{
		for (auto it = uniqueAntinodes.begin(); it != uniqueAntinodes.end(); it++)
		{
			if (lines[it->at(1)][it->at(0)] == '.')
			{
				lines[it->at(1)][it->at(0)] = '#';
			}
		}

		coutList(lines);
	}

	return to_string(uniqueAntinodes.size());
}

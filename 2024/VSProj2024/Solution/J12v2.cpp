#include <FileHandler.h>
#include <iostream>
#include <map>
#include "J12.h"

using namespace std;

string sol12v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<Plot> plots;
	map<vector<size_t>, size_t> posToPlotInd;
	for (size_t y = 0; y < lines.size(); y++)
	{
		string line = lines[y];
		for (size_t x = 0; x < line.size(); x++)
		{
			unsigned b = CountBulkBoundaries(lines, { x,y });
			if (x > 0 && lines[y][x - 1] == line[x])
			{
				size_t plotInd = posToPlotInd[{x - 1, y}];
				Plot* plot = &plots[plotInd];
				plot->Area++;
				plot->Boundary += b;
				posToPlotInd[{x, y}] = plotInd;
			}
			if (y > 0 && lines[y - 1][x] == line[x])
			{
				size_t plotInd = posToPlotInd[{x, y - 1}];
				if (posToPlotInd.find({ x,y }) != posToPlotInd.end())
				{
					if (posToPlotInd[{x, y}] != plotInd)
					{// plotInd already set and different from this one
						size_t plotToRemove = posToPlotInd[{x, y}];
						plots[plotInd] += plots[plotToRemove];
						for (auto it = posToPlotInd.begin(); it != posToPlotInd.end(); it++)
						{
							if (it->second == plotToRemove)
							{
								it->second = plotInd;
							}
						}
						plots[plotToRemove].Area = 0;
					}
				}
				else
				{
					Plot* plot = &plots[plotInd];
					plot->Area++;
					plot->Boundary += b;
					posToPlotInd[{x, y}] = plotInd;
				}
			}
			if ((x == 0 || lines[y][x - 1] != line[x]) &&
				(y == 0 || lines[y - 1][x] != line[x]))
			{
				Plot newPLot(line[x], 1, b);
				plots.push_back(newPLot);
				posToPlotInd[{x, y}] = plots.size() - 1;
			}
		}
	}

	size_t sum = 0;
	for (const Plot& plot : plots)
	{
		size_t mult = plot.Area * plot.Boundary;
		sum += mult;
		if (solutionFileName == "test")
		{
			cout << "Plant " << plot.c << " with price " << plot.Area << " * " << plot.Boundary << " = " << mult << endl;
		}
	}

	return to_string(sum);
}

size_t CountBulkBoundaries(vector<string>& lines, vector<size_t> pos)
{
	size_t boundaries = 0;
	char c = lines[pos[1]][pos[0]];
	if (pos[0] == 0 || lines[pos[1]][pos[0] - 1] != c)
	{
		if (pos[1] == 0 || // on top
			lines[pos[1] - 1][pos[0]] != c || // above is not like me
			(pos[0] > 0 && lines[pos[1] - 1][pos[0] - 1] == c)) // above is like me but I'm in a corner
		{
			boundaries++;
		}
	}
	if (pos[1] == 0 || lines[pos[1] - 1][pos[0]] != c)
	{
		if (pos[0] == 0 || // on the left
			lines[pos[1]][pos[0] - 1] != c || // on the left is not like me
			(pos[1] > 0 && lines[pos[1] - 1][pos[0] - 1] == c)) // on the left is like me but I'm in a corner
		{
			boundaries++;
		}
	}
	if (pos[0] == lines[pos[1]].size() - 1 || lines[pos[1]][pos[0] + 1] != c)
	{
		if (pos[1] == 0 || // on top
			lines[pos[1] - 1][pos[0]] != c || // above is not like me
			(pos[0] < lines[pos[1]].size() - 1 && lines[pos[1] - 1][pos[0] + 1] == c)) // above is like me but I'm in a corner
		{
			boundaries++;
		}
	}
	if (pos[1] == lines.size() - 1 || lines[pos[1] + 1][pos[0]] != c)
	{
		if (pos[0] == 0 || // on the left
			lines[pos[1]][pos[0] - 1] != c || // on the left is not like me
			(pos[1] < lines.size() - 1 && lines[pos[1] + 1][pos[0] - 1] == c)) // on the left is like me but I'm in a corner
		{
			boundaries++;
		}
	}
	return boundaries;
}

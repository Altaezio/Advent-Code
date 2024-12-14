#include <FileHandler.h>
#include <iostream>
#include <map>
#include "J14.h"

using namespace std;
using ll = long long;
using ull = long long;

string sol14v2(string solutionFileName)
{
	return "Start application on J14";
}

vector<vector<ll>> SolveForSeconds(const vector<string>& lines, size_t lapse, int& maxRobot, unsigned& totalInQuads)
{
	maxRobot = 0;
	vector<ull> roomSize{ 101,103 };
	map<vector<ull>, size_t> robotPos;
	vector<unsigned> robotInQuad{ 0,0,0,0 };
	unsigned quadPadding = 2;
	for (string line : lines)
	{
		vector<ll> robot = ExtractllAmongOther(line);
		vector<ll> pos{ robot[0],robot[1] };
		vector<ll> vel{ robot[2],robot[3] };
		ll xAfterLapse = ((ll)(pos[0] + lapse * vel[0]));
		ll yAfterLapse = ((ll)(pos[1] + lapse * vel[1]));
		xAfterLapse = (xAfterLapse % roomSize[0] + roomSize[0]) % roomSize[0];
		yAfterLapse = (yAfterLapse % roomSize[1] + roomSize[1]) % roomSize[1];
		vector<ull> posAfterLapse{ xAfterLapse,yAfterLapse };
		if (robotPos.find(posAfterLapse) != robotPos.end())
		{
			robotPos[{xAfterLapse, yAfterLapse}]++;
		}
		else
		{
			robotPos[{xAfterLapse, yAfterLapse}] = 1;
		}
		if (robotPos[{xAfterLapse, yAfterLapse}] > maxRobot)
		{
			maxRobot = robotPos[{xAfterLapse, yAfterLapse}];
		}

		if (xAfterLapse < roomSize[0] / 2 - quadPadding && yAfterLapse < roomSize[1] / 2 - quadPadding)
		{
			robotInQuad[0]++;
		}
		else if (xAfterLapse > roomSize[0] / 2 + quadPadding && yAfterLapse < roomSize[1] / 2 - quadPadding)
		{
			robotInQuad[1]++;
		}
		else if (xAfterLapse < roomSize[0] / 2 - quadPadding && yAfterLapse > roomSize[1] / 2 + quadPadding)
		{
			robotInQuad[2]++;
		}
		else if (xAfterLapse > roomSize[0] / 2 + quadPadding && yAfterLapse > roomSize[1] / 2 + quadPadding)
		{
			robotInQuad[3]++;
		}
	}
	vector<vector<ll>> linesOut;
	for (ull y = 0; y < roomSize[1]; y++)
	{
		linesOut.push_back({});
		for (ull x = 0; x < roomSize[0]; x++)
		{
			if (robotPos.find({ x,y }) != robotPos.end())
			{
				linesOut[y].push_back(robotPos[{x, y}]);
			}
			else
			{
				linesOut[y].push_back(0);
			}
		}
	}

	totalInQuads = robotInQuad[0] + robotInQuad[1] + robotInQuad[2] + robotInQuad[3];

	return linesOut;
}

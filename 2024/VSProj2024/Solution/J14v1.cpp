#include <FileHandler.h>
#include <iostream>
#include <map>
#include "J14.h"

using namespace std;
using ll = long long;
using ull = long long;

string sol14v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<ull> roomSize{ 101,103 };
	if (solutionFileName == "test")
	{
		roomSize = { 11,7 };
	}
	size_t lapse = 100;

	vector<unsigned> robotInQuad{ 0,0,0,0 };
	map<vector<ull>, size_t> robotPos;
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

		if (xAfterLapse < roomSize[0] / 2 && yAfterLapse < roomSize[1] / 2)
		{
			robotInQuad[0]++;
		}
		else if (xAfterLapse > roomSize[0] / 2 && yAfterLapse < roomSize[1] / 2)
		{
			robotInQuad[1]++;
		}
		else if (xAfterLapse < roomSize[0] / 2 && yAfterLapse > roomSize[1] / 2)
		{
			robotInQuad[2]++;
		}
		else if (xAfterLapse > roomSize[0] / 2 && yAfterLapse > roomSize[1] / 2)
		{
			robotInQuad[3]++;
		}
	}

	size_t mult = robotInQuad[0] * robotInQuad[1] * robotInQuad[2] * robotInQuad[3];

	if (solutionFileName == "test")
	{
		for (ull y = 0; y < roomSize[1]; y++)
		{
			for (ull x = 0; x < roomSize[0]; x++)
			{
				if (robotPos.find({ x,y }) != robotPos.end())
				{
					cout << robotPos[{x, y}];
				}
				else
				{
					cout << ".";
				}
			}
			cout << endl;
		}
	}
	return to_string(mult);
}

#include <iostream>
#include <sstream>
#include <map>
#include "../FileHandler.h"
#include "J15.h"

using namespace std;

string sol15v2()
{
	vector<string> lines = getSolutionLines("J15");

	vector<vector<tuple<string, int>>> hashMaps(256);

	string temp;
	stringstream ss(lines[0]);
	while (getline(ss, temp, ','))
	{
		string strKey = makeKey(temp);
		int key = myHash(strKey);
		vector<tuple<string, int>> box = hashMaps[key];
		if (temp.back() == '-')
		{
			if (box.size() > 0)
			{
				for (size_t i = 0; i < box.size(); i++)
				{
					if (get<0>(box[i]) == strKey)
					{
						hashMaps[key].erase(hashMaps[key].begin() + i);
					}
				}
			}
		}
		else
		{
			bool replaced = false;
			if (box.size() > 0)
			{
				for (size_t i = 0; i < box.size(); i++)
				{
					if (get<0>(box[i]) == strKey)
					{
						get<1>(hashMaps[key][i]) = temp.back() - '0';
						replaced = true;
						break;
					}
				}
			}
			if (!replaced)
			{
				hashMaps[key].push_back(make_tuple(strKey, temp.back() - '0'));
			}
		}
	}
	int sum = 0;
	for (size_t i = 0; i < hashMaps.size(); i++)
	{
		vector<tuple<string, int>> box = hashMaps[i];
		if (box.size() > 0)
		{
			for (size_t j = 0; j < box.size(); j++)
			{
				sum += (i + 1) * (j + 1) * get<1>(box[j]);
			}
		}
	}
	return to_string(sum);
}

string makeKey(std::string word)
{
	size_t lastChar = word.size() - 1 - (word.back() != '-');
	return word.substr(0, lastChar);
}

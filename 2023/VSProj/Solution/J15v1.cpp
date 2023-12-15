#include <iostream>
#include <sstream>
#include "../FileHandler.h"
#include "J15.h"

using namespace std;

string sol15v1()
{
	vector<string> lines = getSolutionLines("J15");

	int sum = 0;
	string temp;
	stringstream ss(lines[0]);
	while (getline(ss, temp, ','))
	{
		sum += myHash(temp);
	}
	return to_string(sum);
}

int myHash(string word)
{
	int value = 0;
	for (char& c : word)
	{
		value = ((value + c) * 17) % 256;
	}
	return value;
}

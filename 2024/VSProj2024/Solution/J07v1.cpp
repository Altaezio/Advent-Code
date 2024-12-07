#include <FileHandler.h>
#include <iostream>
#include "J07.h"

using namespace std;
using ull = unsigned long long;

string sol07v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<function<ull(ull, ull)>> operations;
	operations.push_back(multiplies<ull>());
	operations.push_back(plus<ull>());
	ull sum = 0;
	for (string line : lines)
	{
		size_t delimiter = line.find(':');
		string targetSubStr = line.substr(0, delimiter);
		ull targetNum = stoull(targetSubStr);
		string valuesSubStr = line.substr(delimiter + 1);
		vector<int> operatedValues = ExtractInt(valuesSubStr);
		if (CanBeEqual(operations, operatedValues, targetNum))
		{
			sum += targetNum;
		}
	}
	return to_string(sum);
}

bool CanBeEqual(vector<function<ull(ull, ull)>>& operations,
	vector<int>& values, ull targetValue, bool print)
{
	vector<size_t> operationInd(values.size() - 1, 0);
	size_t totalSwap = pow(operations.size(), operationInd.size());
	for (size_t swap = 0; swap < totalSwap; swap++)
	{
		ull result = values[0];
		for (size_t valueInd = 1; valueInd < values.size(); valueInd++)
		{
			result = operations[operationInd[valueInd - 1]](result, values[valueInd]);
		}

		if (result == targetValue)
		{
			if (print)
			{
				cout << targetValue << " = ";
				for (size_t vInd = 0; vInd < values.size() - 1; vInd++)
				{
					cout << values[vInd];
					if (operations[operationInd[vInd]].target_type() == function(plus<ull>()).target_type())
					{
						cout << " + ";
					}
					else if (operations[operationInd[vInd]].target_type() == function(multiplies<ull>()).target_type())
					{
						cout << " * ";
					}
					else
					{
						cout << " || ";
					}
				}
				cout << values[values.size() - 1] << endl;
			}
			return true;
		}

		if (swap == totalSwap - 1)
		{
			return false;
		}

		int index = operationInd.size() - 1;
		do
		{
			operationInd[index] = (operationInd[index] + 1) % operations.size();
			index--;
		} while (index >= 0 && operationInd[index + 1] == 0);
	}

	return false;
}

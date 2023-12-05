
#include <vector>
#include "../FileHandler.h"
#include "J1.h"

using namespace std;

string sol1v1()
{
	vector<string> lines = getSolutionLines("J1");
	int sum = 0;
	for (string line : lines) {
		string firstDigit = getFirstDigit(line);
		string lastDigit = getLastDigit(line);
		int number = stoi(firstDigit + lastDigit);
		sum += number;
	}
	return to_string(sum);
}

string getFirstDigit(string line)
{
	size_t digitPosition = line.find_first_of("123456789");
	return string(1, line[digitPosition]);
}

string getLastDigit(std::string line)
{
	size_t digitPosition = line.find_last_of("123456789");
	return string(1, line[digitPosition]);
}

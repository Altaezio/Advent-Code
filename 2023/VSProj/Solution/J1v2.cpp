
#include <vector>
#include <string>
#include "../FileHandler.h"
#include "J1.h"
#include <iostream>

using namespace std;

string sol1v2()
{
	vector<string> lines = getSolutionLines("J1");
	int sum = 0;
	for (string line : lines) {
		tfDigitLine(line);
		string firstDigit = getFirstDigit(line);
		string lastDigit = getLastDigit(line);
		int number = stoi(firstDigit + lastDigit);
		sum += number;
	}
	return to_string(sum);
}

void tfDigitLine(string& line)
{
	vector<string> digits{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	for (size_t index = 0; index < digits.size(); index++) {
		string digit = digits[index];
		string::size_type n = line.find(digit);
		if (n != string::npos) {
			line.replace(n + 1, 1, to_string(index + 1));
		}
		n = line.rfind(digit);
		if (n != string::npos) {
			line.replace(n + 1, 1, to_string(index + 1));
		}
	}
}

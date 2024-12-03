#include <FileHandler.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> getSolutionLines(string pathToFile)
{
	vector<string> lines;
	ifstream dataFile("../Input/" + pathToFile + ".txt");
	string line;
	while (getline(dataFile, line)) {
		lines.push_back(line);
	}
	return lines;
}

void coutList(vector<string> list)
{
	for (string line : list)
	{
		cout << line << endl;
	}
}

vector<string> Extract(const string& Text) {
	vector<string> Words;
	stringstream ss(Text);
	string Buf;

	while (ss >> Buf)
		Words.push_back(Buf);

	return Words;
}

vector<int> ExtractInt(const string& Text) {
	vector<int> numbers;
	stringstream ss(Text);
	string Buf;

	while (ss >> Buf)
		numbers.push_back(stoi(Buf));

	return numbers;
}

vector<long long> Extractll(const string& Text) {
	vector<long long> numbers;
	stringstream ss(Text);
	string Buf;

	while (ss >> Buf)
		numbers.push_back(stoll(Buf));

	return numbers;
}

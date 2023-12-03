#include "FileHandler.h"
#include <fstream>
#include <iostream>

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

void coutList(std::vector<string> list)
{
    for (string line : list)
    {
        cout << line << endl;
    }
}

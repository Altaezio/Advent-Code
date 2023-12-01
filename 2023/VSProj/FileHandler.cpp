#include "FileHandler.h"
#include <fstream>

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

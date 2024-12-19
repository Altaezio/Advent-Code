#include <FileHandler.h>
#include <iostream>
#include <ppl.h>
#include "J17.h"

using namespace std;

string sol17v2(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<long long> baseRegisters;
	baseRegisters.push_back(ExtractllAmongOther(lines[0])[0]);
	baseRegisters.push_back(ExtractllAmongOther(lines[1])[0]);
	baseRegisters.push_back(ExtractllAmongOther(lines[2])[0]);

	string programStr = &lines[4][9];
	vector<long long> program = ExtractllAmongOther(programStr);

	/*size_t x = 0;
	while (true)
	{
		string out;
		vector<long long> registers{ x,baseRegisters[1],baseRegisters[2] };
		Solve(baseRegisters, program, out);
		cout << "a: " << x << " out: " << out << endl;
		x++;
	}*/

	/*
	size_t nParallel = 1000;
	long long a = 0;
	string finalOutput;
	size_t finalA = numeric_limits<size_t>::max();
	while (finalOutput != programStr)
	{
		vector<long long> aTested;
		for (size_t i = 0; i < nParallel; i++)
		{
			aTested.push_back(a + i);
		}
		Concurrency::parallel_for(size_t(0), nParallel, [&](size_t i)
			{
				string output;
				vector<long long> registers{ aTested[i],baseRegisters[1],baseRegisters[2] };
				size_t pointer = 0;
				while (pointer < program.size() && (output.size() == 0 || (output.size() <= programStr.size() && output.back() == programStr[output.size() - 1])))
				{
					DoInstruction(registers, pointer, program[pointer], program[pointer + 1], output);
				}
				if (output == programStr && aTested[i] < finalA)
				{
					finalOutput = output;
					finalA = aTested[i];
				}
			});
		cout << "\r" << "a: " << a;
		a++;
	}
	cout << endl;
	return to_string(finalA);
	*/

	// for legacy purpose mdr
	size_t testValue = 0;

	string output;
	for (size_t inversedTestedBit = 0; inversedTestedBit < program.size(); inversedTestedBit++)
	{
		size_t testedBitInd = program.size() - inversedTestedBit - 1;
		long long a = 0;
		size_t goodTested = 0;
		size_t maxTest = pow(2, 3 * testedBitInd);
		for (size_t tested = 0; tested < maxTest; tested++)
		{
			output.clear();
			a = tested;// testValue + tested * pow(2, 3);
			vector<long long> registers{ a,baseRegisters[1],baseRegisters[2] };
			Solve(registers, program, output);
			cout << "a: " << a << " out: " << output << endl;
			if (output.size() > 0 &&
				output[0] == programStr[testedBitInd * 2])
			{
				goodTested = tested;
				break;
			}
		}
		cout << endl;
		//cout << "Bit: " << testedBitInd << " valid: " << testValue << " out: " << output << endl;
		if (output != programStr)
		{
			testValue += goodTested * pow(2, 3 * (testedBitInd + 1));
		}
	}

	return to_string(testValue);
}

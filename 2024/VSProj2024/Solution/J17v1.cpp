#include <FileHandler.h>
#include <iostream>
#include "J17.h"

using namespace std;

string sol17v1(string solutionFileName)
{
	vector<string> lines = getSolutionLines(solutionFileName);
	vector<long long> registers;
	registers.push_back(ExtractllAmongOther(lines[0])[0]);
	registers.push_back(ExtractllAmongOther(lines[1])[0]);
	registers.push_back(ExtractllAmongOther(lines[2])[0]);

	vector<long long> program = ExtractllAmongOther(lines[4]);

	size_t pointer = 0;
	string output;
	while (pointer < program.size())
	{
		DoInstruction(registers, pointer, program[pointer], program[pointer + 1], output);
	}

	return output;
}

void DoInstruction(vector<long long>& registers, size_t& pointer, size_t opcode, size_t literalOperand, string& out)
{
	size_t combOperand = literalOperand;
	if (literalOperand == 4)
	{
		combOperand = registers[0];
	}
	if (literalOperand == 5)
	{
		combOperand = registers[1];
	}
	if (literalOperand == 6)
	{
		combOperand = registers[2];
	}
	if (opcode == 0)
	{
		registers[0] = registers[0] / pow(2, combOperand);
	}
	else if (opcode == 1)
	{
		registers[1] = registers[1] ^ literalOperand;
	}
	else if (opcode == 2)
	{
		registers[1] = combOperand % 8;
	}
	else if (opcode == 3 && registers[0] != 0)
	{
		pointer = literalOperand;
		return;
	}
	else if (opcode == 4)
	{
		registers[1] = registers[1] ^ registers[2];
	}
	else if (opcode == 5)
	{
		if (out.size() > 0)
		{
			out.append(",");
		}
		out.append(to_string(combOperand % 8));
	}
	else if (opcode == 6)
	{
		registers[1] = registers[0] / pow(2, combOperand);
	}
	else if (opcode == 7)
	{
		registers[1] = registers[0] / pow(2, combOperand);
	}
	pointer += 2;
}

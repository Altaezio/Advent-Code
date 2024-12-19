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

	string output;
	Solve(registers, program, output);

	return output;
}
size_t GetCombOperand(vector<long long>& registers, size_t opcode, size_t literalOperand)
{
	size_t combOperand = literalOperand;
	if (literalOperand == 4)
	{
		combOperand = registers[0];
	}
	else if (literalOperand == 5)
	{
		combOperand = registers[1];
	}
	else if (literalOperand == 6)
	{
		combOperand = registers[2];
	}
	return combOperand;
}

void DoInstruction(vector<long long>& registers, size_t& pointer, size_t opcode, size_t literalOperand, string& out)
{
	if (opcode == 0)
	{
		registers[0] = (double)registers[0] / pow(2, GetCombOperand(registers, opcode, literalOperand));
	}
	else if (opcode == 1)
	{
		registers[1] = registers[1] ^ literalOperand;
	}
	else if (opcode == 2)
	{
		registers[1] = GetCombOperand(registers, opcode, literalOperand) % 8;
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
		out.append(to_string(GetCombOperand(registers, opcode, literalOperand) % 8));
	}
	else if (opcode == 6)
	{
		registers[1] = (double)registers[0] / pow(2, GetCombOperand(registers, opcode, literalOperand));
	}
	else if (opcode == 7)
	{
		registers[2] = (double)registers[0] / pow(2, GetCombOperand(registers, opcode, literalOperand));
	}
	pointer += 2;
}

void Solve(vector<long long>& registers, const vector<long long>& program, string& out)
{
	size_t pointer = 0;
	while (pointer < program.size())
	{
		DoInstruction(registers, pointer, program[pointer], program[pointer + 1], out);
	}
}

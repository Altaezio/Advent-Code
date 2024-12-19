#pragma once

std::string sol17v1(std::string solutionFileName);
std::string sol17v2(std::string solutionFileName);

size_t GetCombOperand(std::vector<long long>& registers, size_t opcode, size_t operand);

void DoInstruction(std::vector<long long>& registers, size_t& pointer, size_t opcode, size_t operand, std::string& out);

void Solve(std::vector<long long>& registers, const std::vector<long long>& program, std::string& out);

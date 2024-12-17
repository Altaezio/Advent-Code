#pragma once

std::string sol17v1(std::string solutionFileName);
std::string sol17v2(std::string solutionFileName);

void DoInstruction(std::vector<long long>& registers, size_t& pointer, size_t opcode, size_t operand, std::string& out);

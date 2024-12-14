#pragma once

std::string sol14v1(std::string solutionFileName);
std::string sol14v2(std::string solutionFileName);

std::vector<std::vector<long long>> SolveForSeconds(const std::vector<std::string>& lines, size_t lapse,
	int& maxRobot, unsigned& totalInQuads);

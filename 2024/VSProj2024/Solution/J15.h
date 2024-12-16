#pragma once

std::string sol15v1(std::string solutionFileName);
std::string sol15v2(std::string solutionFileName);

std::vector<size_t> MoveRobotOrCreate(std::vector<std::string>& map, const std::vector<size_t>& position, char direction);

bool CanMoveRobotOrBigCreate(std::vector<std::string>& map, std::vector<size_t>& position, char direction);
void DoMoveRobotOrBigCreate(std::vector<std::string>& map, std::vector<size_t>& position, char direction);

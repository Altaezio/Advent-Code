#pragma once

std::string sol14v1();
std::string sol14v2();

int tiltInDirection(std::vector<std::string>& lines, const std::pair<int, int> direction);

std::pair<size_t, size_t> findFirstEmpty(const std::vector<std::string>& lines, std::pair<size_t, size_t> start, std::pair<int, int> direction);

std::vector<std::pair<size_t, size_t>> getRocks(const std::vector<std::string>& lines);

void sortRocks(std::vector<std::pair<size_t, size_t>>& rocks, const int tilt);

int tiltInAnyDirection(std::vector<std::string>& lines, std::vector<std::pair<size_t, size_t>>& rocks, const std::pair<int, int> direction);

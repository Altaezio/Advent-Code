#pragma once

std::string sol14v1();
std::string sol14v2();

int tiltInDirection(std::vector<std::string>& lines, std::pair<int, int> direction);

std::pair<size_t, size_t> findFirstEmpty(std::vector<std::string>& lines, std::pair<size_t, size_t> start, std::pair<int, int> direction);

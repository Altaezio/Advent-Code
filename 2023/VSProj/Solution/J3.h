#pragma once

std::string sol3v1();
std::string sol3v2();

bool oneNeighbourIsSymbol(std::vector < std::string > lines, size_t lineIndex, size_t begin, size_t end);

bool getGearNeighbour(std::vector < std::string > lines, size_t lineIndex, size_t begin, size_t end, std::tuple<size_t, size_t>& outGearPosition);

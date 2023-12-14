#pragma once

std::string sol13v1();
std::string sol13v2();

std::vector<std::vector<std::string>> getPatterns(std::vector<std::string>& lines);

int getPatternValue(std::vector<std::string>& pattern);

size_t verticalSymmetry(std::vector<std::string>& pattern);
size_t horizontalSymmetry(std::vector<std::string>& pattern);

bool isVerticalySymmetricFromIndex(std::vector<std::string>& pattern, size_t refIndex);
bool isHorizontalySymmetricFromIndex(std::vector<std::string>& pattern, size_t refIndex);

bool areColumnsEquals(std::vector<std::string>& pattern, size_t aIndex, size_t bIndex);

int getPatternValueV2(std::vector<std::string>& pattern);
size_t symetryV2(std::vector<std::string>& pattern, int (*countDiff)(std::vector<std::string>&, size_t, size_t), size_t highLimit);

bool isSymetricFromIndex(std::vector<std::string>& pattern, size_t refIndex, int (*countDiff)(std::vector<std::string>&, size_t, size_t), size_t highLimit);

int countDiffVertical(std::vector<std::string>& pattern, size_t aIndex, size_t bIndex);
int countDiffHorizontal(std::vector<std::string>& pattern, size_t aIndex, size_t bIndex);

#pragma once

std::string sol5v1();
std::string sol5v2();

long long getValueInterval(std::vector<std::vector<std::vector<long long>>>& intervals, long long value);

long long getValueIntervalRange(std::vector<std::vector<std::vector<long long>>>& intervals, std::vector<std::vector<long long>> seeds);

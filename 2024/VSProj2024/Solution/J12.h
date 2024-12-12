#pragma once

std::string sol12v1(std::string solutionFileName);
std::string sol12v2(std::string solutionFileName);

struct Plot
{
	char c;
	size_t Area = 0;
	size_t Boundary = 0;

	Plot(char c, size_t area, size_t boundary) : c(c), Area(area), Boundary(boundary) {};

	Plot& operator+=(const Plot& b)
	{
		Area += b.Area;
		Boundary += b.Boundary;
		return *this;
	}
};

size_t CountBoundaries(std::vector<std::string>& lines, std::vector<size_t> pos);

size_t CountBulkBoundaries(std::vector<std::string>& lines, std::vector<size_t> pos);

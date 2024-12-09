#include <FileHandler.h>
#include <iostream>
#include "J09.h"

using namespace std;

string sol09v2(string solutionFileName)
{
	struct File
	{
		int ID = 0;
		size_t size = 0;
	};

	vector<string> lines = getSolutionLines(solutionFileName);
	size_t sum = 0;
	vector<File> disk;
	for (string line : lines)
	{
		size_t beginBlockID = 0;
		for (size_t i = 0; i < line.size(); i += 2)
		{
			int block = line[i] - '0';

			File file;
			file.ID = beginBlockID;
			file.size = block;
			disk.push_back(file);
			beginBlockID++;

			if (i + 1 < line.size())
			{
				int spaceSize = line[i + 1] - '0';
				if (spaceSize > 0)
				{
					File space;
					space.ID = -1;
					space.size = spaceSize;
					disk.push_back(space);
				}
			}
		}
	}

	for (size_t i = disk.size() - 1; i > 0; i--)
	{
		File* fileToMove = &disk[i];
		if (fileToMove->ID == -1)
		{
			continue;
		}
		for (size_t j = 0; j < i; j++)
		{
			File* file = &disk[j];
			if (file->ID != -1 ||
				file->size < fileToMove->size)
			{
				continue;
			}
			disk.insert(disk.begin() + j, *fileToMove);
			i++;
			disk[i].ID = -1;
			if (i + 1 < disk.size() && disk[i + 1].ID == -1)
			{
				disk[i].size += disk[i + 1].size;
				disk.erase(disk.begin() + i + 1);
			}
			if (disk[i - 1].ID == -1)
			{
				disk[i - 1].size += disk[i].size;
				disk.erase(disk.begin() + i);
				i--;
			}
			fileToMove = &disk[j];
			j++;
			file = &disk[j];
			file->size -= fileToMove->size;
			if (file->size == 0)
			{
				disk.erase(disk.begin() + j);
			}
			break;
		}
	}

	size_t ind = 0;
	for (auto it = disk.begin(); it != disk.end(); it++)
	{
		for (size_t i = 0; i < it->size; i++)
		{
			if (it->ID != -1)
			{
				sum += ind * it->ID;
			}
			ind++;
		}
	}

	return to_string(sum);
}

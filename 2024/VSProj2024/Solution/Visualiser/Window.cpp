#include "Window.h"
#include <iostream>
#include <FileHandler.h>
#include <AStar.h>
#include "..\J06.h"
#include "..\J14.h"
#include "..\J15.h"
#include "..\J18.h"


using namespace std;

Window* Window::Instance = NULL;

Window* Window::GetInstance(string fileName)
{
	if (!Instance)
	{
		Instance = new Window(fileName);
	}
	if (fileName != Instance->fileName)
	{
		return nullptr; // TODO:: better assert
	}
	return Instance;
}

#pragma region J06

void Window::ShowJ06()
{
	if (lines.size() <= 0)
	{
		return;
	}


	float cellWidthPercent = 1.00f / lines[0].size();
	float cellHeightPercent = 1.00f / lines.size();

	for (size_t lineIndex = 0; lineIndex < lines.size(); lineIndex++)
	{
		string line = lines[lineIndex];
		for (size_t cellIndex = 0; cellIndex < lines[0].size(); cellIndex++)
		{
			char c = line[cellIndex];
			if (c == '#')
			{
				float x1 = -1.0f + 2 * cellIndex * cellWidthPercent;
				float y1 = 1.0f - 2 * lineIndex * cellHeightPercent;
				float x2 = -1.0f + 2 * (cellIndex + 1) * cellWidthPercent;
				float y2 = 1.0f - 2 * (lineIndex + 1) * cellHeightPercent;
				glColor3f(1.0f, 1.0f, 1.0f); // black
				glRectf(x1, y1, x2, y2);
			}
		}
	}
	for (vector<int> visitedPos : visited)
	{
		float x1 = -1.0f + 2 * visitedPos[0] * cellWidthPercent;
		float y1 = 1.0f - 2 * visitedPos[1] * cellHeightPercent;
		float x2 = -1.0f + 2 * (visitedPos[0] + 1) * cellWidthPercent;
		float y2 = 1.0f - 2 * (visitedPos[1] + 1) * cellHeightPercent;
		glColor3f(.5f, .5f, .5f); // gray
		glRectf(x1, y1, x2, y2);
	}

	glBegin(GL_TRIANGLES);
	float x1 = -1.0f + 2 * ((direction[0] == -1) ? currentPos[0] + 1 : currentPos[0]) * cellWidthPercent;
	float x2 = -1.0f + 2 * ((direction[0] == 1 ? currentPos[0] + 1 : currentPos[0]) + 0.5f * abs(direction[1])) * cellWidthPercent;
	float x3 = -1.0f + 2 * (direction[0] == 1 ? currentPos[0] : currentPos[0] + 1) * cellWidthPercent;
	float y1 = 1.0f - 2 * (direction[0] + direction[1] < 0 ? currentPos[1] + 1 : currentPos[1]) * cellHeightPercent;
	float y2 = 1.0f - 2 * ((direction[1] == 1 ? currentPos[1] + 1 : currentPos[1]) + 0.5f * abs(direction[0])) * cellWidthPercent;
	float y3 = 1.0f - 2 * (direction[1] == -1 || direction[0] == 1 ? currentPos[1] + 1 : currentPos[1]) * cellHeightPercent;

	glColor3f(.0f, .0f, 1.0f); // blue
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();
}

void Window::ProcessJ06(bool solveAll)
{
	if (currentPos[0] == -1 && currentPos[1] == -1)
	{
		currentPos = GetStartingPoint(lines);
	}

	while (currentPos[0] >= 0 &&
		currentPos[1] >= 0 &&
		currentPos[1] < lines.size() &&
		currentPos[0] < lines[currentPos[1]].size())
	{
		if (DoMove(lines, direction, currentPos))
		{
			visited.insert(currentPos);
		}

		if (!solveAll)
		{
			cout << "direction: " << direction[0] << " ; " << direction[1] << endl;
			break;
		}
	}
	if (currentPos[0] < 0 ||
		currentPos[1] < 0 ||
		currentPos[1] >= lines.size() ||
		currentPos[0] >= lines[currentPos[1]].size())
	{
		cout << "Out of the map" << endl;
	}
}

#pragma endregion

#pragma region J10

void Window::ShowJ10()
{
	if (lines.size() <= 0)
	{
		return;
	}

	float cellWidthPercent = 1.00f / lines[0].size();
	float cellHeightPercent = 1.00f / lines.size();

	vector<float> color0{ 0.0f,0.1f,0.8f };
	vector<float> color9{ 0.8f,0.6f,0.5f };

	for (size_t lineIndex = 0; lineIndex < lines.size(); lineIndex++)
	{
		string line = lines[lineIndex];
		for (size_t cellIndex = 0; cellIndex < line.size(); cellIndex++)
		{
			float x1 = -1.0f + 2 * cellIndex * cellWidthPercent;
			float y1 = 1.0f - 2 * lineIndex * cellHeightPercent;
			float x2 = -1.0f + 2 * (cellIndex + 1) * cellWidthPercent;
			float y2 = 1.0f - 2 * (lineIndex + 1) * cellHeightPercent;

			float t = (float)(line[cellIndex] - '0') / ('9' - '0');
			vector<float> color(3, 0.0f);
			for (size_t i = 0; i < 3; i++)
				color[i] = lerp(color0[i], color9[i], t);
			glColor3f(color[0], color[1], color[2]);

			glRectf(x1, y1, x2, y2);
		}
	}
}

#pragma endregion

#pragma region J14

void Window::ShowJ14()
{
	if (currentRoom.size() <= 0)
	{
		return;
	}

	float cellWidthPercent = 1.00f / currentRoom[0].size();
	float cellHeightPercent = 1.00f / currentRoom.size();

	vector<float> color0{ 0.0f,0.0f,0.0f };
	vector<float> colorMax{ 1.0f,1.0f,1.0f };

	for (size_t lineIndex = 0; lineIndex < currentRoom.size(); lineIndex++)
	{
		vector<long long> line = currentRoom[lineIndex];
		for (size_t cellIndex = 0; cellIndex < line.size(); cellIndex++)
		{
			float x1 = -1.0f + 2 * cellIndex * cellWidthPercent;
			float y1 = 1.0f - 2 * lineIndex * cellHeightPercent;
			float x2 = -1.0f + 2 * (cellIndex + 1) * cellWidthPercent;
			float y2 = 1.0f - 2 * (lineIndex + 1) * cellHeightPercent;

			float t = 0.0f;
			if (line[cellIndex] != 0)
			{
				t = (float)(line[cellIndex]) / maxRobot;
			}
			vector<float> color(3, 0.0f);
			for (size_t i = 0; i < 3; i++)
				color[i] = lerp(color0[i], colorMax[i], t);
			glColor3f(color[0], color[1], color[2]);

			glRectf(x1, y1, x2, y2);
		}
	}
}

void Window::NextStepJ14()
{
	unsigned inQuads = 0;
	vector<int> add{ 23,89 };
	size_t currentLapse = 0;
	if (ind % 2 == 0)
	{
		currentLapse = add[0] + ind * 101;
	}
	else
	{
		currentLapse = add[1] + ind * 103;
	}
	cout << "\r" << "l: " << currentLapse;
	currentRoom = SolveForSeconds(lines, currentLapse, maxRobot, inQuads);
	cout << " ; inQuads: " << inQuads;
	ind++;
}

#pragma endregion

#pragma region J15

void Window::ShowJ15()
{
	if (currentMap.size() < 1)
	{
		return;
	}


	float cellWidthPercent = 1.00f / currentMap[0].size();
	float cellHeightPercent = 1.00f / currentMap.size();

	vector<float> wallColor{ 0.5f,0.5f,0.5f };
	vector<float> robotColor{ 1.0f,1.0f,1.0f };
	vector<float> createColor{ 0.75f,0.5f,0.0f };


	for (size_t lineIndex = 0; lineIndex < currentMap.size(); lineIndex++)
	{
		string line = currentMap[lineIndex];
		for (size_t cellIndex = 0; cellIndex < line.size(); cellIndex++)
		{
			float x1 = -1.0f + 2 * cellIndex * cellWidthPercent;
			float y1 = 1.0f - 2 * lineIndex * cellHeightPercent;
			float x2 = -1.0f + 2 * (cellIndex + 1) * cellWidthPercent;
			float y2 = 1.0f - 2 * (lineIndex + 1) * cellHeightPercent;

			vector<float> color(3, 0.0f);
			if (line[cellIndex] == '#')
			{
				color = wallColor;
			}
			else if (line[cellIndex] == '.')
			{
				continue;
			}
			else if (line[cellIndex] == '@')
			{
				color = robotColor;
			}
			else if (line[cellIndex] == 'O' || line[cellIndex] == '[' || line[cellIndex] == ']')
			{
				color = createColor;
			}
			glColor3f(color[0], color[1], color[2]);

			glRectf(x1, y1, x2, y2);
		}
	}
}

void Window::NextStepJ15v1()
{
	if (currentMap.size() == 0)
	{
		for (size_t y = 0; y < lines.size(); y++)
		{
			string line = lines[y];
			if (line.size() < 2)
			{
				currentInstruction.push_back(0);
				currentInstruction.push_back(y + 1);
				break;
			}
			currentMap.push_back(line);
			if (currentRobotPosition.size() == 0)
			{
				size_t start = line.find('@');
				if (start != string::npos)
				{
					currentRobotPosition.push_back(start);
					currentRobotPosition.push_back(y);
				}
			}
		}
	}
	else if (currentInstruction[1] < lines.size())
	{
		currentRobotPosition = MoveRobotOrCreate(currentMap, currentRobotPosition, lines[currentInstruction[1]][currentInstruction[0]]);
		currentInstruction[0]++;
		if (currentInstruction[0] == lines[currentInstruction[1]].size())
		{
			currentInstruction[0] = 0;
			currentInstruction[1]++;
		}
	}
}
void Window::NextStepJ15v2(bool solveAll)
{
	if (currentMap.size() == 0)
	{
		for (size_t y = 0; y < lines.size(); y++)
		{
			string line = lines[y];
			if (line.size() < 2)
			{
				currentInstruction.push_back(0);
				currentInstruction.push_back(y + 1);
				break;
			}
			string newLine;
			for (size_t x = 0; x < line.size(); x++)
			{
				if (lines[y][x] == '#')
				{
					newLine.append("##");
				}
				else if (lines[y][x] == 'O')
				{
					newLine.append("[]");
				}
				else if (lines[y][x] == '.')
				{
					newLine.append("..");
				}
				else if (lines[y][x] == '@')
				{
					newLine.append("@.");
					currentRobotPosition.push_back(2 * x);
					currentRobotPosition.push_back(y);
				}
			}
			currentMap.push_back(newLine);
		}
		if (!solveAll)
		{
			return;
		}
	}
	while (currentInstruction.size() != 0 && currentInstruction[1] < lines.size())
	{
		if (CanMoveRobotOrBigCreate(currentMap, currentRobotPosition, lines[currentInstruction[1]][currentInstruction[0]]))
		{
			DoMoveRobotOrBigCreate(currentMap, currentRobotPosition, lines[currentInstruction[1]][currentInstruction[0]]);
		}
		currentInstruction[0]++;
		if (currentInstruction[0] == lines[currentInstruction[1]].size())
		{
			currentInstruction[0] = 0;
			currentInstruction[1]++;
		}
		if (!solveAll)
		{
			break;
		}
	}
}

#pragma endregion

#pragma region J18

void Window::ShowJ18()
{
	if (currentMap.size() == 0)
	{
		return;
	}


	float cellWidthPercent = 1.00f / currentMap[0].size();
	float cellHeightPercent = 1.00f / currentMap.size();

	vector<float> corruptedColor{ 0.56f,0.0f,0.56f };
	vector<float> pathColor{ 1.0f,1.0f,1.0f };
	vector<float> visitedColor{ 0.5f,0.5f,0.5f };


	for (size_t lineIndex = 0; lineIndex < currentMap.size(); lineIndex++)
	{
		string line = currentMap[lineIndex];
		for (size_t cellIndex = 0; cellIndex < line.size(); cellIndex++)
		{
			float x1 = -1.0f + 2 * cellIndex * cellWidthPercent;
			float y1 = 1.0f - 2 * lineIndex * cellHeightPercent;
			float x2 = -1.0f + 2 * (cellIndex + 1) * cellWidthPercent;
			float y2 = 1.0f - 2 * (lineIndex + 1) * cellHeightPercent;

			vector<float> color(3, 0.0f);
			if (line[cellIndex] == '#')
			{
				color = corruptedColor;
			}
			else if (line[cellIndex] == '.')
			{
				continue;
			}
			else if (line[cellIndex] == 'O')
			{
				color = pathColor;
			}
			else if (line[cellIndex] == '|')
			{
				color = visitedColor;
			}
			glColor3f(color[0], color[1], color[2]);

			glRectf(x1, y1, x2, y2);
		}
	}
}

void Window::NextStepJ18()
{
	if (currentMap.size() == 0)
	{
		vector<string> lines = getSolutionLines(fileName);
		spaceSize = { 71,71 };
		if (fileName == "test")
		{
			spaceSize = { 7,7 };
		}
		for (size_t y = 0; y < spaceSize[1]; y++)
		{
			string line(spaceSize[0], '.');
			currentMap.push_back(line);
		}
		corruptionLevel = 0;
		maxCorruptionLevel = lines.size();
	}
	else if (corruptionLevel < maxCorruptionLevel)
	{
		while (true)
		{
			size_t comma = lines[corruptionLevel].find(',');
			vector<size_t> pos;
			pos.push_back(stoull(lines[corruptionLevel].substr(0, comma)));
			pos.push_back(stoull(lines[corruptionLevel].substr(comma + 1, lines[corruptionLevel].size() - comma)));
			currentMap[pos[1]][pos[0]] = '#';
			if (currentPath.size() == 0 || find(currentPath.begin(), currentPath.end(), pos) != currentPath.end())
			{
				for (string& line : currentMap)
				{
					for (char& c : line)
					{
						if (c != '#')
						{
							c = '.';
						}
					}
				}

				Node start(2, { 0,0 }, 0, 0);
				Node end(2, { spaceSize[0] - 1,spaceSize[1] - 1 });
				map<vector<size_t>, Node> visited;
				vector<Node> path = GetShortestPath<Node>(currentMap, start, end, CreateNode, SimpleIsAtObjective, SimpleGetNeighbours2D, &visited);
				for (auto it = visited.begin(); it != visited.end(); it++)
				{
					currentMap[it->first[1]][it->first[0]] = '|';
				}
				currentPath.clear();
				for (Node& node : path)
				{
					currentPath.push_back(node.position);
					currentMap[node.position[1]][node.position[0]] = 'O';
				}
				cout << endl << "Corruption Level : " << corruptionLevel << " with " << end.cost << " steps" << endl;
				break;
			}
			corruptionLevel += 1;
		}
	}
}

#pragma endregion


Window::Window(string fileName) : window(), fileName(fileName)
{
	lines = getSolutionLines(fileName);
}

Window::~Window()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

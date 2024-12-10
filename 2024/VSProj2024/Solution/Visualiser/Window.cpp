#include "Window.h"
#include <iostream>
#include <FileHandler.h>
#include "..\J06.h"

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

Window::Window(string fileName) : window(), fileName(fileName)
{
	lines = getSolutionLines(fileName);
}

Window::~Window()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

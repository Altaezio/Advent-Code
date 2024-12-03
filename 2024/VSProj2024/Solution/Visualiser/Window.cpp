#include "Window.h"
#include <iostream>
#include <FileHandler.h>

using namespace std;

Window* Window::Instance = NULL;

Window* Window::GetInstance()
{
	if (!Instance)
	{
		Instance = new Window();
	}
	return Instance;
}

void Window::drawRockMap()
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
			char character = line[cellIndex];
			if (character == 'O')
			{
				float x1 = -1.0f + 2 * cellIndex * cellWidthPercent;
				float y1 = 1.0f - 2 * lineIndex * cellHeightPercent;
				float x2 = -1.0f + 2 * (cellIndex + 1) * cellWidthPercent;
				float y2 = 1.0f - 2 * (lineIndex + 1) * cellHeightPercent;
				glColor3f(.8f, .6f, .4f); // clear brown
				glRectf(x1, y1, x2, y2);
			}
			if (character == '#')
			{
				float x1 = -1.0f + 2 * cellIndex * cellWidthPercent;
				float y1 = 1.0f - 2 * lineIndex * cellHeightPercent;
				float x2 = -1.0f + 2 * (cellIndex + 1) * cellWidthPercent;
				float y2 = 1.0f - 2 * (lineIndex + 1) * cellHeightPercent;
				glColor3f(.5f, .2f, .1f); // browner brown
				glRectf(x1, y1, x2, y2);
			}
		}
	}
}

void Window::tilt(const int direction)
{
}

Window::Window() : window()
{
	directions = { make_pair(-1,0),make_pair(0,-1), make_pair(1,0), make_pair(0,1) };
	lines = getSolutionLines("J14");
}

Window::~Window()
{
	//glfwSetWindowShouldClose(window, GLFW_TRUE);
}

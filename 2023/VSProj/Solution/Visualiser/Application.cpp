#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../FileHandler.h"
#include "../J14.h"

using namespace std;

int StartApplication()
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	const int width = 900;
	const int height = 900;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	vector<string> lines = getSolutionLines("J14");

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		drawRockMap(lines);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void drawRockMap(const vector<string>& lines)
{
	//vector<string> lines;
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

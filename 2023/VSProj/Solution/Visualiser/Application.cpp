#include "Application.h"
#include <GLFW/glfw3.h>
#include "../../FileHandler.h"
#include "../J14.h"

using namespace std;

int StartApplication()
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	const int WIDTH = 500;
	const int HEIGHT = 500;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		vector<string> lines = getSolutionLines("J14");
		drawRockMap(lines);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void drawRockMap(vector<string>& lines)
{
	float cellWidthPercent = 1.0f / lines[0].size();
	float cellHeightPercent = 1.0f / lines.size();

	for (size_t lineIndex = 0; lineIndex < lines.size(); lineIndex++)
	{
		string line = lines[lineIndex];
		for (size_t cellIndex = 0; cellIndex < lines[0].size(); cellIndex++)
		{
			char character = line[cellIndex];
			if (character == 'O')
			{
				float x1 = -1.0f + cellIndex * cellWidthPercent;
				float y1 = 1.0f - cellIndex * cellHeightPercent;
				float x2 = -1.0f + cellIndex * cellWidthPercent;
				float y2 = 1.0f - cellIndex * cellHeightPercent;
				_ASSERT(x1 >= -1.0f);
				_ASSERT(x1 <= 1.0f);
				_ASSERT(y1 >= -1.0f);
				_ASSERT(y1 <= 1.0f);
				_ASSERT(x2 >= -1.0f);
				_ASSERT(x2 <= 1.0f);
				_ASSERT(y2 >= -1.0f);
				_ASSERT(y2 <= 1.0f);
				glRectf(x1, y1, x2, y2);
			}
		}
	}
}

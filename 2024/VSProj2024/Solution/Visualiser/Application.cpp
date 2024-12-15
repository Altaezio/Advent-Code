#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"

using namespace std;

int StartApplication(string fileName)
{
	Window* myWindow = Window::GetInstance(fileName);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	const int width = 900;
	const int height = 900;

	/* Create a windowed mode window and its OpenGL context */
	myWindow->window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	GLFWwindow* window = myWindow->window;
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;
	double baseIteration = 100.01; // in seconds
	double nextIteration = baseIteration;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		myWindow->ShowJ15();

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		nextIteration -= deltaTime;
		if (nextIteration < 0.0)
		{
			Window::GetInstance("J15")->NextStepJ15v2(false);
			nextIteration += baseIteration;
		}

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
	if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Window::GetInstance("test")->ProcessJ06(false);
		//Window::GetInstance("J14")->NextStepJ14();
		Window::GetInstance("J15")->NextStepJ15v2(true);
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		//Window::GetInstance("test")->ProcessJ06(true);
	}
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
	{
		//Window::GetInstance()->tilt(0); // north
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		//Window::GetInstance()->tilt(2); // south
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
	{
		//Window::GetInstance()->tilt(1); // west
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
	{
		//Window::GetInstance()->tilt(3); // est
	}
}

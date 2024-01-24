#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <string>


class Window {
public:
	static Window* GetInstance();

	GLFWwindow* window;

	void drawRockMap();
	void tilt(const int direction);
private:
	Window();
	~Window();

	std::vector<std::string> lines;
	std::vector<std::pair<size_t, size_t>> rocks;
	std::vector<std::pair<int, int>> directions;

	static Window* Instance;
};


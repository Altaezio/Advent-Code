#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <set>


class Window {
public:
	static Window* GetInstance(std::string fileName);

	GLFWwindow* window;

	void ShowJ06();
	void ProcessJ06(bool solveAll);

	void ShowJ10();

	void ShowJ14();
	void NextStepJ14();

private:
	Window(std::string fileName);
	~Window();

	std::string fileName;
	std::vector<std::string> lines;

	// --J06 data--
	std::vector<int> currentPos{ -1,-1 };
	std::vector<int> direction{ 0,-1 };
	std::set<std::vector<int>> visited;
	// --

	// --J14 data--
	int maxRobot = 0;
	int ind = 0;
	std::vector<std::vector<long long>> currentRoom;
	// --

	static Window* Instance;
};


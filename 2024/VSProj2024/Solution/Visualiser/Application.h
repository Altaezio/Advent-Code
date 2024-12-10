#pragma once
#include <string>
#include <vector>
#include <GLFW/glfw3.h>

int StartApplication(std::string fileName);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

//void drawCircle(float cx, float cy, float r, int num_segments); https://dev.to/ishaqkassam/drawing-a-circle-using-opengl-glfwglew-c-1247

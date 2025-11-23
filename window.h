#pragma once

#include "Vertex.h"
#include <GLFW/glfw3.h>

class RenderWindow
{
public:
	
	RenderWindow(int width, int height, const char* title);

	int Init();

	void Draw();

	int End();

	void Run();

	int windowWidth;
	int windowHeight;

	Triangle* tri;

	const char* windowName;
	GLFWwindow* window;
};

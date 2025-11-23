#pragma once
#include "window.h"


RenderWindow::RenderWindow(int width, int height, const char* title)
{
	windowWidth = width;
	windowHeight = height;
	windowName = title;
	
	Init();

	tri = new Triangle();
	tri->Init();
}

int RenderWindow::Init()
{

	if (!glfwInit())
	{
		return -1;
	}


	window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	
}

void RenderWindow::Draw()
{
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);

		tri->Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	End();
}

int RenderWindow::End()
{
	glfwTerminate();
	return 0;
}

void RenderWindow::Run() 
{
	Draw();
}



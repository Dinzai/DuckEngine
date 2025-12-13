#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <vector>
#include <string>
#include <iostream>


struct Vec2
{
	float x = 0.0f;
	float y = 0.0f;
};

class RenderWindow
{
public:
	
	RenderWindow(int width, int height, const char* title);

	int Init();

	void Draw();

	//void KeyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods);

	int End();

	void Run();

	int windowWidth;
	int windowHeight;


	const char* windowName;
	GLFWwindow* window;

	std::vector<float> verticies = 
    {
        0.5f, 0.5f, 0.0f, 1.0, 0.0, 0.0,
        -0.5f, 0.5f, 0.0f, 0.0, 1.0, 0.0,
        -0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0,
		0.5f, -0.5f, 0.0f, 1.0, 1.0, 0.0
    };

	std::vector<unsigned int> indicies = {
		0, 1, 2,
		0, 2, 3
	};

	std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
		layout (location = 1) in vec3 color;

		uniform vec2 uOffset;

		out vec3 vColor;
		

        void main()
        {
			vColor = color;
            gl_Position = vec4(position.x + uOffset.x, position.y + uOffset.y, position.z, 1.0);
        }

    )";

	std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

		in vec3 vColor;
		uniform vec4 uColor;

        void main()
        {
            FragColor = vec4(vColor, 1.0) * uColor;
        }

    )";


	

	GLuint vbo;
	GLuint vao;

	GLuint ibo;

	GLuint uColorLoc;

	GLuint uOffsetLoc;

	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;


};

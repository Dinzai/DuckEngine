
#include "window.h"

RenderWindow::RenderWindow(int width, int height, const char *title)
{
	windowWidth = width;
	windowHeight = height;
	windowName = title;

	Init();
}
Vec2 offset;

void KeyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		switch(key)
		{
		case GLFW_KEY_UP:
			offset.y += 0.01f;
			//std::cout << "Up" << std::endl;
			break;

		case GLFW_KEY_DOWN:
			offset.y -= 0.01f;
			//std::cout << "Down" << std::endl;
			break;

		case GLFW_KEY_LEFT:
			offset.x -= 0.01f;
			//std::cout << "Left" << std::endl;
			break;

		case GLFW_KEY_RIGHT:
			offset.x += 0.01f;
			//std::cout << "Right" << std::endl;
			break;

		default: 
			break;

		}
	}
}

int RenderWindow::Init()
{

	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, KeyCallBack);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		glfwTerminate();
		return -1;
	}

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char *vertexShaderCstr = vertexShaderSource.c_str();

	glShaderSource(vertexShader, 1, &vertexShaderCstr, nullptr);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "Vertex shader compilation fail: " << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fragmentShaderCstr = fragmentShaderSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentShaderCstr, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "Fragment shader compilation fail: " << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "Program Linker fail: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), verticies.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	uColorLoc = glGetUniformLocation(shaderProgram, "uColor");

	uOffsetLoc = glGetUniformLocation(shaderProgram, "uOffset");

	

	return 0;
}

void RenderWindow::Draw()
{
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glUniform4f(uColorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
		glUniform2f(uOffsetLoc, offset.x, offset.y);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	End();
}

int RenderWindow::End()
{
	glfwTerminate();
	return 1;
}

void RenderWindow::Run()
{
	Draw();
}

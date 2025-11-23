#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vector3 //vertex
{
	float x;
	float y;
	float z;
};

class VShader 
{
public:
	VShader();

	const char* vertexShaderSource;
	unsigned int vertexShader;

};

class FShader
{
public:
	FShader();

	const char* fragShaderSource;
	unsigned int fragmentShader;

};

class ShaderProgram 
{
public:

	ShaderProgram();

	VShader* vertexShader;
	FShader* fragmentShader;

	unsigned int shaderProgram;
};

class Triangle 
{
public:
	Triangle();

	void Init();

	void Draw();

	float verts[9];

	ShaderProgram* shader;
	unsigned int VAO;
	unsigned int VBO;

};

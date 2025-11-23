#include "Vertex.h"

VShader::VShader()
{
	vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
	glCompileShader(vertexShader);

}

FShader::FShader()
{
	fragShaderSource = "#version 330 core\n"
		"out vec4 fragColor;\n"
		"void main()\n"
		"{\n"
		"	fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragShaderSource, 0);
	glCompileShader(fragmentShader);

}

ShaderProgram::ShaderProgram() 
{
	shaderProgram = glCreateProgram();
	vertexShader = new VShader();
	fragmentShader = new FShader();

	glAttachShader(shaderProgram, vertexShader->vertexShader);
	glAttachShader(shaderProgram, fragmentShader->fragmentShader);
	glLinkProgram(shaderProgram);
}

Triangle::Triangle() 
	: verts{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f

	}
{
	shader = new ShaderProgram();
	
}

void Triangle::Init() 
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Triangle::Draw() 
{
	glUseProgram(shader->shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

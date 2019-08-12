#include "Shader.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>

int Shader::loadShader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);
	if (vertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}
	else {
		std::cout << "Impossible to open " << vertexShaderPath << ". Are you in the right directory ? Don't forget to read the FAQ !\n" << std::endl;
		getchar();
		return 0;
	}

	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragmentShaderPath, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	std::cout << "Compiling shader : " << vertexShaderPath << std::endl;
	char const * VertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << &VertexShaderErrorMessage[0] << std::endl;
	}

	// Compile Fragment Shader
	std::cout << "Compiling shader : " << fragmentShaderPath << std::endl;
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cout << &FragmentShaderErrorMessage[0] << std::endl;
	}

	// Link the program
	std::cout << "Linking program" << std::endl;
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShaderID);
	glAttachShader(ProgramID, fragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
	}

	glDetachShader(ProgramID, vertexShaderID);
	glDetachShader(ProgramID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return ProgramID;
}
#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>

class Shader {
public:
	unsigned int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

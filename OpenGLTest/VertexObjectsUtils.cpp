#include "VertexObjectsUtils.h"

#include <glad/glad.h>

void VertexObjectsUtils::initBuffers(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO) {
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	if (EBO != nullptr) {
		glGenBuffers(1, EBO);
	}
}

void VertexObjectsUtils::bindBuffers(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, std::vector<float> vertices, std::vector<int> indexes) {
	if (*VAO == NULL || *VBO == NULL) {
		throw std::runtime_error("Initialize the vertex objects before binding them!");
	}
	// 1. bind Vertex Array Object
	glBindVertexArray(*VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
	if (EBO != nullptr && !indexes.empty()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(int), &indexes.front(), GL_STATIC_DRAW);
	}
	else {
		throw std::runtime_error("EBO null or indexes empty!");
	}
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
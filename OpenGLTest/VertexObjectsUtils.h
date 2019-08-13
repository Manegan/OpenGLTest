#pragma once

#include <vector>

class VertexObjectsUtils {
public:
	void initBuffers(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO);
	void bindBuffers(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, std::vector<float> vertices, std::vector<int> indexes);
};

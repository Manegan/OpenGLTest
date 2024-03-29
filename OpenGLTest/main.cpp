#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <stdexcept>

#include "Shader.h"
#include "VertexObjectsUtils.h"

const uint32_t WIDTH = 1024;
const uint32_t HEIGHT = 768;

class OpenGLApp {
public:
	void run() {
		initWindow();
		mainLoop();
		cleanup();
	}

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

private:
	Shader* shader = NULL;
	GLFWwindow* window;
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		//0.5f, 0.5f, 0.0f
	};

	std::vector<int> indexes = {
	};
	unsigned int VBO, VAO,
		programID;

	VertexObjectsUtils vertexObjectsUtils;

	void initWindow() {
		if (!glfwInit()) {
			throw std::runtime_error("Failed to init glfw!");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
		
		window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL App", nullptr, nullptr);
		if (window == nullptr) {
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window!");
		}

		glfwMakeContextCurrent(window);

		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			glfwTerminate();
			throw std::runtime_error("Failed to initialize GLAD");
		}

		shader = new Shader("SimpleVertexShader.vert", "SimpleFragmentShader.frag");

		vertexObjectsUtils.initBuffers(&VAO, &VBO, NULL);
		vertexObjectsUtils.bindBuffers(&VAO, &VBO, NULL, vertices, indexes);
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			processInput();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->use();

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void processInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	void cleanup() {
		glfwDestroyWindow(window);

		glfwTerminate();
	}
};

int main() {
	OpenGLApp app;
	try {
		app.run();
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
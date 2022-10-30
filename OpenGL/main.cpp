#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.hpp"
#include <iostream>

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);

void glfwErrorCallback(int error, const char* description)
{
	std::cout << "GLFW error: " << error << " " << description << "\n";
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{	
		glfwSetWindowShouldClose(window, 1);
	}
}

int main()
{
	if (!glfwInit())
		std::cout << "Could not Initialize GLFW!\n";

	glfwSetErrorCallback(glfwErrorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearningOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to Initialize GLEW!\n";
		return 1;
	}
	
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetKeyCallback(window, glfwKeyCallback);
	glfwSwapInterval(1);

	glViewport(0, 0, 800, 600);

	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	Shader vertexShader = Shader("VertexShader.glsl", GL_VERTEX_SHADER);

	Shader fragmentShader = Shader("FragmentShader.glsl", GL_FRAGMENT_SHADER);

	unsigned int shaderProgram = createShaderProgram();

	float colors[] = { 0.9f, 0.3f, 0.4f, 1.0f };
	glUseProgram(shaderProgram);
	fragmentShader.SetUniformValue("ourColor", shaderProgram, colors);

	glDeleteShader(vertexShader.ID);
	glDeleteShader(fragmentShader.ID);

	float vertexPositions[12] = {
	   0.5f, 0.5f, 0.0f,
	   0.5f, -0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f,
	  -0.5f, 0.5f, 0.0f,
	};

	unsigned int indeces[6] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int vertexArrayObject;
	unsigned int ElementBufferObject;
	unsigned int vertexBuffer;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertexPositions, GL_STATIC_DRAW);

	glGenBuffers(1, &ElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indeces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUseProgram(shaderProgram);

	const double fpsLimit = 1.0 / 60.0;
	double lastUpdateTime = 0;
	double lastFrameTime = 0;

	while (!glfwWindowShouldClose(window))
	{
		double now = glfwGetTime();
		double deltaTime = now - lastUpdateTime;

		glfwPollEvents();

		if ((now - lastFrameTime) >= fpsLimit)
		{
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vertexArrayObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			glfwSwapBuffers(window);

			lastFrameTime = now;
		}

		lastUpdateTime = now;
	}

	glDeleteProgram(shaderProgram);	

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

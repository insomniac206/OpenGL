#pragma once

#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Shader
{
public:
	unsigned int ID;

	Shader(std::string shaderPath, unsigned int shaderType);

	unsigned int compileShader(std::string shaderSource, unsigned int shaderType);

private:
	unsigned int m_shaderType;
	std::string m_shaderSource;
};

extern std::vector<unsigned int> ShaderList;

/* Adds a compiled shader to a global list of shaders (std::vector<unsigned int> ShaderList), for use later in creating a linked shader program */
void addShader(unsigned int shaderID); 

/* Creates a linked shader program */
unsigned int CreateShaderProgram();

/* Deletes all shaders and removes them from the list (std::vector<unsigned int> ShaderList) */
void cleanupShaders();
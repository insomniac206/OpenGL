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
};
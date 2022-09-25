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

	template<typename valueType>
	void SetUniformValue(std::string uniformName, unsigned int shaderProgram, valueType values[])
	{
		int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());

		if constexpr (std::is_integral_v<valueType>)
		{
			glUniform4i(uniformLocation, values[0], values[1], values[2], values[3]);
		}
		else if constexpr (std::is_floating_point_v<valueType>)
		{
			glUniform4f(uniformLocation, values[0], values[1], values[2], values[3]);
		}
	}
};
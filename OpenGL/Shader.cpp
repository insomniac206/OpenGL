#include "Shader.hpp"

Shader::Shader(std::string shaderPath, unsigned int shaderType)
{

	if (shaderPath == "" && shaderType == 0)
		return;

	std::ifstream sSourceStream;

	sSourceStream.open(shaderPath);

	std::string line;
	std::stringstream ShaderSource;
	while (std::getline(sSourceStream, line))
	{
		ShaderSource << line << "\n";
	}
	sSourceStream.close();

	Shader::ID = compileShader(ShaderSource.str(), shaderType);
}


unsigned int Shader::compileShader(std::string shaderSource, unsigned int shaderType)
{
	unsigned int shader = glCreateShader(shaderType);
	const char* ShaderSource = shaderSource.c_str();

	glShaderSource(shader, 1, &ShaderSource, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* infoLog = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, infoLog);
		std::cout << "Shader Compilation Failed: " << infoLog << std::endl;
		glDeleteShader(shader);
	}

	return shader;
}
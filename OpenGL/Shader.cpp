#include "Shader.hpp"

std::vector<unsigned int> ShaderList = {};

Shader::Shader(std::string shaderPath, unsigned int shaderType)
{
	std::ifstream sSourceStream;

	sSourceStream.open(shaderPath);

	std::string line;
	std::stringstream ShaderSource;
	while (std::getline(sSourceStream, line))
	{
		ShaderSource << line << "\n";
	}
	sSourceStream.close();

	Shader::m_shaderSource = ShaderSource.str();
	Shader::m_shaderType = shaderType;

	Shader::ID = compileShader(Shader::m_shaderSource, Shader::m_shaderType);
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

void addShader(unsigned int shaderID)
{
	std::vector<unsigned int>::iterator lastElement = ShaderList.end();
	ShaderList.insert(lastElement, shaderID);
}

unsigned int CreateShaderProgram()
{
	unsigned int shaderProgram = glCreateProgram();

	std::vector<unsigned int>::iterator CurrentElement = ShaderList.begin();
	for (auto i : ShaderList)
	{
		glAttachShader(shaderProgram, *CurrentElement);
		CurrentElement++;
	}

	glLinkProgram(shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		int length;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
		char* infoLog = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Shader Program linking failed: " << infoLog << '\n';
		glDeleteProgram(shaderProgram);
	}

	return shaderProgram;
}

void cleanupShaders()
{
	std::vector<unsigned int>::iterator CurrentElement = ShaderList.begin();
	for (auto i : ShaderList)
	{
		glDeleteShader(*CurrentElement);
		CurrentElement++;
	}
}
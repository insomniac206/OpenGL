#include "Shader.hpp"

static std::vector<unsigned int> shaderList;

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

	unsigned int shader = glCreateShader(shaderType);
	std::string sSourceString = ShaderSource.str();
	const char* shaderSource = sSourceString.c_str();

	glShaderSource(shader, 1, &shaderSource, nullptr);
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
	Shader::ID = shader;
	shaderList.push_back(Shader::ID);
}




unsigned int createShaderProgram()
{
	unsigned int shaderProgram = glCreateProgram();
	
	for (auto i : shaderList)
	{
		glAttachShader(shaderProgram, i);
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
		return 0;
	}

	return shaderProgram;
}
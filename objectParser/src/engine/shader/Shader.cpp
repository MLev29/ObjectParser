#include "Shader.h"
#include "tools/FileData.h"

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <exception>

#include "tools/MemoryCheck.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>

#ifndef SHADER_RELATIVE_PATH
#define SHADER_RELATIVE_PATH "..\\..\\..\\objectParser\\src\\shaders\\"
#endif

Shader::Shader(const char* vertFileName, const char* fragFileName)
	: m_vertFileName(vertFileName), m_fragFileName(fragFileName), m_programID(0)
{
}

void Shader::InitShaders(void)
{
	unsigned int vertexShader = InitShader(m_vertFileName);
	unsigned int fragmentShader = InitShader(m_fragFileName);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	
	glLinkProgram(m_programID);
	
	int success;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	
	if (!success)
	{
		constexpr int bufferSize = 2500;
		char infoLog[bufferSize];
	
		glGetProgramInfoLog(m_programID, bufferSize, nullptr, infoLog);
		std::printf("Failed to link shader program, reason: %s\n", infoLog);
	
		return;
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use(void) const
{
	glUseProgram(m_programID);
}

void Shader::SetMatrix4(const char* name, math::Matrix4<float>* matrix)
{
	int location = glGetUniformLocation(m_programID, name);

	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix->m_matrix[0][0]);
}

void Shader::SetBool(const char* name, bool value)
{
	glUniform1i(glGetUniformLocation(m_programID, name), static_cast<int>(value));
}

void Shader::SetInt(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(m_programID, name), value);
}

void Shader::SetFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(m_programID, name), value);
}

void Shader::SetVec3(const char* name, math::Vector3<float>& vec3) const
{
	glUniform3f(glGetUniformLocation(m_programID, name), vec3[0], vec3[1], vec3[2]);
}

unsigned int Shader::GetProgramID(void) const noexcept
{
	return m_programID;
}

const char* Shader::GetVertexName(void) const noexcept
{
	return m_vertFileName;
}

const char* Shader::GetFragName(void) const noexcept
{
	return m_fragFileName;
}

unsigned int Shader::InitShader(const char* fileName)
{

	int fileType = ShaderType(fileName);

	unsigned int shader = glCreateShader(fileType);

	char relativePath[256] = SHADER_RELATIVE_PATH;
	strcat_s(relativePath, fileName);

	objParser::FileData fileData = fileData.ReadFile(relativePath);

	glShaderSource(shader, 1, &fileData.m_fileContent, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		constexpr int infoLogLength = 2500;
		char infoLog[infoLogLength];
	
		glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
		std::printf("Failed to compile shader, reason: %s\n", infoLog);
	
		return 0;
	}

	fileData.Clear();

	return shader;
}

std::string Shader::ReadShaderFile(std::filesystem::path& filePath)
{
	try
	{
		std::ifstream shaderFile(filePath, std::ios::in | std::ios::binary);

		std::stringstream sStream;

		sStream << shaderFile.rdbuf();

		shaderFile.close();

		return sStream.str();
	}
	catch (std::ifstream::failure& exception)
	{
		std::stringstream sStream;
		sStream << "Failed to read shader file, reason: " << exception.what() << '\n';

		throw std::exception(sStream.str().c_str());
	}
}

int Shader::ShaderType(const char* fileName)
{
	std::vector<const char*> vertexShaderExtensions{"vs", "vert"};
	std::vector<const char*> fragmentShaderExtensions{"fs", "frag"};

	GLenum fileType = GL_INVALID_ENUM;
	size_t pos = std::string(fileName).rfind('.');

	if (pos == std::string::npos)
	{
		std::printf("Given shader file does not have an extension\n");
		return 0;
	}

	std::string extensionStr = std::string(fileName).substr(pos + 1, std::string::npos).c_str();

	size_t max = (vertexShaderExtensions.size() >= fragmentShaderExtensions.size()) ?
		vertexShaderExtensions.size() : fragmentShaderExtensions.size();

	for (int i = 0; i < static_cast<int>(max); ++i)
	{
		if (std::strcmp(extensionStr.c_str(), vertexShaderExtensions[i]) == 0)
			fileType = GL_VERTEX_SHADER;
		else if (std::strcmp(extensionStr.c_str(), fragmentShaderExtensions[i]) == 0)
			fileType = GL_FRAGMENT_SHADER;
	}

	if (fileType == GL_INVALID_ENUM)
		std::printf("Shader file '%s' contains unsupported extension\n", fileName);

	return fileType;
}

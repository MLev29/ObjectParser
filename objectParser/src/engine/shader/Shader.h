#pragma once

#include "LibMath/Matrix/Matrix4.h"

#include <filesystem>
#include <string>
#include "tools/MemoryCheck.h"

class Shader
{
public:
					Shader(const char* vertFileName, const char* fragFileName);
					~Shader(void) = default;

	void			InitShaders(void);
	void			Use(void) const;

	void			SetMatrix4(const char* name, math::Matrix4<float>* matrix);
	void			SetBool(const char* name, bool value);
	void			SetInt(const char* name, int value);
	void			SetFloat(const char* name, float value);
	void			SetVec3(const char* name, math::Vector3<float>& vec3) const;

	unsigned int	GetProgramID(void) const noexcept;
	const char*		GetVertexName(void) const noexcept;
	const char*		GetFragName(void) const noexcept;

private:
	unsigned int	InitShader(const char* fileName);
	std::string		ReadShaderFile(std::filesystem::path& filePath);
	int				ShaderType(const char* fileName);

	const char*		m_vertFileName;
	const char*		m_fragFileName;
	unsigned int	m_programID;
};
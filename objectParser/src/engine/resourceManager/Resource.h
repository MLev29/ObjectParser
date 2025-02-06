#pragma once

#include "shader/Shader.h"
#include "tools/MemoryCheck.h"

namespace objParser
{
	class Resource
	{
	public:
		Resource(void) = default;
		virtual ~Resource(void) = default;

		virtual void LoadResource(const char* filePath) = 0;
		virtual void Update(Shader* shader) = 0;
	private:
	};
}
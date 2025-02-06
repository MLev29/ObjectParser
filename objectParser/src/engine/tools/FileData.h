#pragma once
#include <memory>
#include "MemoryCheck.h"

namespace objParser
{
	struct FileData
	{
		FileData(void) = default;
		FileData(char* fileContent, size_t size)
			: m_fileContent(fileContent), m_size(size)
		{
		}

		FileData ReadFile(const char* filePath)
		{
			FILE* file;
			fopen_s(&file, filePath, "rb");

			if (file)
			{
				fseek(file, 0, SEEK_END);
				m_size = ftell(file);

				m_fileContent = static_cast<char*>(calloc(m_size + 1, sizeof(char)));
				fseek(file, 0, SEEK_SET);
				fread(m_fileContent, sizeof(char), m_size, file);

				fclose(file);
			}

			return *this;
		}

		void Clear(void)
		{
			if (m_fileContent)
				free(m_fileContent);

			m_fileContent = nullptr;
			m_size = 0;
		}

		char* m_fileContent;
		size_t m_size;
	};
}
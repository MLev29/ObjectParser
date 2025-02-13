#include "Model.h"
#include "Vertex.h"

#include <fast_float/fast_float.h>

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MODEL_RELATIVE_PATH "..\\..\\assets\\model\\"

objParser::Model::Model(void)
	: m_vao(0), m_vbo(0), m_ebo(0), m_indexCount(0)
{
	m_meshData = nullptr;
	m_transform = Transform();
}

void objParser::Model::LoadResource(const char* filename)
{
	char relativePath[256] = MODEL_RELATIVE_PATH;
	strcat_s(relativePath, filename);

	FileData fileData = fileData.ReadFile(relativePath);

	// Check file contains valid model data
	if (fileData.m_size == 0)
		return;

	SetMemBlockSize(fileData.m_size);

	// Allocate memory for vertex & index data
	m_meshData = (objParser::ModelData*) malloc(sizeof(objParser::ModelData));
	*m_meshData = objParser::ModelData();

	ParseFileV2(fileData);

	Buffers();

	m_meshData->PostLoad(m_indexCount);
	free(m_meshData);
	fileData.Clear();
}

void objParser::Model::Update(Shader* shader)
{
	if (this)
	{
		math::Matrix4<float> model = GetModelMatrix();
		shader->SetMatrix4("model", &model);
		shader->SetVec3("objectColor", m_color);

		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void objParser::Model::SetPosition(math::Vector3<float> newPos)
{
	m_transform.m_position = newPos;
}

void objParser::Model::SetScale(math::Vector3<float> newScale)
{
	m_transform.m_scale = newScale;
}

void objParser::Model::SetColor(math::Vector3<float> color)
{
	m_color = color;
}

math::Matrix4<float> objParser::Model::GetModelMatrix(void) const noexcept
{
	math::Matrix4<float> modelMatrix;

	modelMatrix.m_matrix[0][3] = m_transform.m_position[0];
	modelMatrix.m_matrix[1][3] = m_transform.m_position[1];
	modelMatrix.m_matrix[2][3] = m_transform.m_position[2];

	modelMatrix.m_matrix[0][0] = m_transform.m_scale[0];
	modelMatrix.m_matrix[1][1] = m_transform.m_scale[1];
	modelMatrix.m_matrix[2][2] = m_transform.m_scale[2];

	return modelMatrix.Transpose();
}

void objParser::Model::ParseFileV2(FileData const& data)
{
	const char* start = data.m_fileContent;
	const char* end = start + 1;

	while (*end != '\0')
	{
		bool skipLine = true;

		if (*start == 'v' ||
			*start == 'f')
		{
			// skip to next line
			skipLine = false;
		}

		if (*end == '\n' || *end == '\r')
		{
			// End of line

			// Store line data
			if (!skipLine)
			{
				// Process data into vertex
				ParseLine(start, end);
			}


			char nextChar = *(end + 1);
			if (nextChar == '\n')
				++end;

			if (nextChar != '\0')
				start = end + 1;
		}

		++end;
	}
}

void objParser::Model::Buffers(void)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	size_t vSize = sizeof(math::Vector3<float>) * m_meshData->m_positions.Size();
	size_t vtSize = sizeof(math::Vector2<float>) * m_meshData->m_texCoords.Size();
	size_t vnSize = sizeof(math::Vector3<float>) * m_meshData->m_normals.Size();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vSize + vtSize + vnSize, nullptr, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, m_meshData->m_positions.m_data);
	glBufferSubData(GL_ARRAY_BUFFER, vSize, vtSize, m_meshData->m_texCoords.m_data);
	glBufferSubData(GL_ARRAY_BUFFER, vSize + vtSize, vnSize, m_meshData->m_normals.m_data);

	vSize = sizeof(int) * m_meshData->m_indices.Size();
	vtSize = sizeof(int) * m_meshData->m_texCoordIndices.Size();
	vnSize = sizeof(int) * m_meshData->m_normalIndices.Size();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vSize + vtSize + vnSize, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, vSize, m_meshData->m_indices.m_data);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, vSize, vtSize, m_meshData->m_texCoordIndices.m_data);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, vSize + vtSize, vnSize, m_meshData->m_normalIndices.m_data);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void objParser::Model::HandleNegativeIndices(int& index, int type)
{
	switch (type)
	{
		case 0: // Position index
			index = m_meshData->m_positions.Size() + index + 1;
			break;
		case 1: // Texture index
			index = m_meshData->m_texCoords.Size() + index + 1;
			break;
		case 2: // Normal index
			index = m_meshData->m_normals.Size() + index + 1;
			break;
		default:
			break;
	}
}

void objParser::Model::ParseLine(const char* start, const char* end)
{
	switch (*start)
	{
		case 'v':
			ParseVertex(start);
			break;
		case 'f':
			ParseFace(start, end);
			break;
		default:
			break;
	}
}

void objParser::Model::ParseVertex(const char* start)
{
	switch (*(start + 1))
	{
		case ' ':
			m_meshData->m_positions.Append(StrToVec3(start));
			break;
		case 'n':
			m_meshData->m_normals.Append(StrToVec3(start));
			break;
		case 't':
			m_meshData->m_texCoords.Append(StrToVec2(start));
			break;
		default:
			break;
	}
}

void objParser::Model::ParseFace(const char* start, const char* end)
{
	const char* startPos = start + 2;
	const char* cursorPos = startPos;

	Index indices[192];
	int index = 0;

	while (1)
	{
		if (*cursorPos == ' ' ||
			cursorPos == end)
		{
			indices[index] = ParseFaceSegment(startPos, cursorPos);
			++index;

			if (cursorPos != end)
				startPos = cursorPos + 1;
			else
				break;
		}

		++cursorPos;
	}

	// Handle quads / ngons
	TrigIndices(indices, index);

	// Add to buffer
	for (int i = 0; i < index; ++i)
	{
		// Position index
		m_meshData->m_indices.Append(indices[i].m_pos - 1);

		// Normal index
		if (indices[i].m_norm != 0)
			m_meshData->m_normalIndices.Append(indices[i].m_norm - 1);

		// Texture coordinate index
		if (indices[i].m_texCoord != 0)
			m_meshData->m_texCoordIndices.Append(indices[i].m_texCoord - 1);
	}
}

objParser::Index objParser::Model::ParseFaceSegment(const char* start, const char* end)
{
	const char* cursorPos = start + 1;
	const char* startPos = start;

	Index index;

	/*
		Options:
		- v
		- v/vt
		- v//vn
		- v/vt/vn

		v -> vt -> vn
	*/
	int i = 0;
	while (i < 3)
	{
		if (*cursorPos == '/' ||
			cursorPos == end)
		{
			fast_float::from_chars(startPos, cursorPos, index[i], 10);

			// Negative index
			if (index[i] < 0)
				HandleNegativeIndices(index[i], i);

			++i;

			if (cursorPos != end &&
				*(cursorPos + 1) == '/')
			{
				cursorPos += 2;
				startPos = cursorPos;
				++i;
			}
			else if (cursorPos != end)
				startPos = cursorPos + 1;
			else
				break;
		}

		++cursorPos;
	}

	return index;
}

void objParser::Model::TrigIndices(objParser::Index* inIndices, int& indexCount)
{
	switch (indexCount)
	{
		case 3:
			break;
		case 4:
			HandleQuad(inIndices);
			indexCount = 6;
			break;
		default:
			HandlePolygon(inIndices, indexCount);
			break;
	}
}

void objParser::Model::HandleQuad(objParser::Index* inIndices)
{
	inIndices[5] = inIndices[3];
	inIndices[3] = inIndices[0];
	inIndices[4] = inIndices[2];
}

void objParser::Model::HandlePolygon(objParser::Index* indices, int& count)
{
	int newCount = 0;

	objParser::Index inIndices[64];
	for (int i = 0; i < count; ++i)
	{
		inIndices[i] = indices[i];
	}

	for (int i = 0; i < count - 2; ++i)
	{
		indices[newCount]		= inIndices[0];
		indices[newCount + 1]	= inIndices[i + 1];
		indices[newCount + 2]	= inIndices[i + 2];

		newCount += 3;
	}

	count = newCount;
}

void objParser::Model::SetMemBlockSize(int charCount)
{
	g_memoryBlockSize = charCount / 10;
}

math::Vector2<float> objParser::Model::StrToVec2(const char* line)
{
	math::Vector2<float> vec2;
	const char* cursorPos = line + 3;
	const char* start = line;
	int index = 0;

	while (index < 2)
	{
		if (start == line &&
			(*cursorPos >= '0' &&
			 *cursorPos <= '9') ||
			*cursorPos == '-')
		{
			// Start pos found
			start = cursorPos;
		}

		if (start != line &&
			(*cursorPos < '0' ||
			 *cursorPos > '9') &&
			*cursorPos != '-' &&
			*cursorPos != '.')
		{
			fast_float::from_chars(start, cursorPos, vec2[index]);
			start = line;
			++index;
		}

		++cursorPos;
	}

	return vec2;
}

math::Vector3<float> objParser::Model::StrToVec3(const char* line)
{
	math::Vector3<float> vec3;
	const char* cursorPos = line + 2;
	const char* start = line;
	int index = 0;

	while (index < 3)
	{
		if (start == line &&
		   (*cursorPos >= '0' &&
			*cursorPos <= '9') ||
			*cursorPos == '-')
		{
			// Start pos found
			start = cursorPos;
		}

		if (start != line &&
			(*cursorPos < '0' ||
			*cursorPos > '9') &&
			*cursorPos != '-' &&
			*cursorPos != '.')
		{
			fast_float::from_chars(start, cursorPos, vec3[index]);
			//vec3[index] = strtof(start, (char**) &cursorPos);
			start = line;
			++index;
		}

		++cursorPos;
	}

	return vec3;
}

// Index Code
int objParser::Index::operator[](int index) const noexcept
{
	switch (index)
	{
		case 0:
			return m_pos;
		case 1:
			return m_texCoord;
		case 2:
		default:
			return m_norm;
	}
}

int& objParser::Index::operator[](int index) noexcept
{
	switch (index)
	{
		case 0:
			return m_pos;
		case 1:
			return m_texCoord;
		case 2:
		default:
			return m_norm;
	}
}

objParser::ModelData::ModelData(void)
{
	m_positions = DataArray<math::Vector3<float>>();
	m_normals = DataArray<math::Vector3<float>>();
	m_texCoords = DataArray<math::Vector2<float>>();
	m_indices = DataArray<int>();
	m_texCoordIndices = DataArray<int>();
	m_normalIndices = DataArray<int>();
}

void objParser::ModelData::PostLoad(int& indexCount)
{
	indexCount = m_indices.Size();

	m_positions.Clear();
	m_normals.Clear();
	m_texCoords.Clear();
	m_indices.Clear();
	m_texCoordIndices.Clear();
	m_normalIndices.Clear();
}

objParser::Transform::Transform(void)
	: m_position(0.0f), m_rotation(0.0f), m_scale(1.0f)
{
}

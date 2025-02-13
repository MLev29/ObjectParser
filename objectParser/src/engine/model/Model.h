#pragma once

#define ENABLE_MULTITHREAD 0

#include "tools/FileData.h"
#include "DataArray.h"
#include "resourceManager/Resource.h"

#include "LibMath/vector/Vector2.h"
#include "LibMath/vector/Vector3.h"

#include <vector>
#include "tools/MemoryCheck.h"

/*
*	TODO:
*	- Handle clearing memory	DONE
*	- Handle polygons (ngons)	DONE
*	- Handle negative indices	DONE
*	- Handle material files
*/

namespace objParser
{
	struct Transform
	{
		Transform(void);
		~Transform(void) = default;
		
		math::Vector3<float> m_position;
		math::Vector3<float> m_rotation;
		math::Vector3<float> m_scale;
	};

	struct Index
	{
		Index(void) = default;
		~Index(void) = default;

		int operator[](int index) const noexcept;
		int& operator[](int index) noexcept;

		int m_pos = 0;
		int m_texCoord = 0;
		int m_norm = 0;
	};

	struct ModelData
	{
		ModelData(void);
		~ModelData(void) = default;

		void PostLoad(int& indexCount);

		DataArray<math::Vector3<float>>	m_positions;
		DataArray<math::Vector3<float>>	m_normals;
		DataArray<math::Vector2<float>>	m_texCoords;
		DataArray<int>					m_indices;
		DataArray<int>					m_texCoordIndices;
		DataArray<int>					m_normalIndices;
	};

	class Model final : public Resource
	{
	public:
								Model(void);
		virtual					~Model(void) = default;

		virtual void			LoadResource(const char* filename) override;
		virtual void			Update(Shader* shader) override;

		void					SetPosition(math::Vector3<float> newPos);
		void					SetScale(math::Vector3<float> newScale);
		void					SetColor(math::Vector3<float> color);
		math::Matrix4<float>	GetModelMatrix(void) const noexcept;
	private:
		void					ParseFileV2(FileData const& data);
		void					Buffers(void);
		void					HandleNegativeIndices(int& index, int type);
		void					ParseLine(const char* start, const char* end);
		void					ParseVertex(const char* start);
		void					ParseFace(const char* start, const char* end);
		objParser::Index		ParseFaceSegment(const char* start, const char* end);
		void					TrigIndices(objParser::Index* inIndices, int& indexCount);
		void					HandleQuad(objParser::Index* indices);
		void					HandlePolygon(objParser::Index* indices, int& count);
		void					SetMemBlockSize(int charCount);

		math::Vector2<float>	StrToVec2(const char* line);
		math::Vector3<float>	StrToVec3(const char* line);

		ModelData*				m_meshData;
		Transform				m_transform;
		math::Matrix4<float>	m_modelMatrix;
		math::Vector3<float>	m_color;
		unsigned int			m_vao;
		unsigned int			m_vbo;
		unsigned int			m_ebo;
		int						m_indexCount;
	};
}
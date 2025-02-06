#pragma once

#include "Resource.h"
#include "shader/Shader.h"

#include <mutex>
#include <unordered_map>

#include "tools/MemoryCheck.h"

namespace objParser
{
	class ResourceManager
	{
	public:
		static ResourceManager*		GetInstance(void);

		template<typename T>
		void				Load(std::string const& fileName);
		template<typename T>
		T*					GetResource(std::string const& fileName);
		void				Unload(std::string const& fileName);
		void				UnloadAll(void);
		void				Update(Shader* shader);
		void				CloseResourceManager(void);
	private:
							ResourceManager(void) = default;
							ResourceManager(ResourceManager const& rManager) = delete;
		ResourceManager&	operator=(ResourceManager const& rManager) = delete;


		static std::mutex		m_mutex;
		static ResourceManager* m_instance;

		std::unordered_map<std::string, Resource*> m_resources;
	};

	template<typename T>
	inline void ResourceManager::Load(std::string const& fileName)
	{
		m_resources[fileName] = new T();
		m_resources[fileName]->LoadResource(fileName.c_str());
	}

	template<typename T>
	inline T* ResourceManager::GetResource(std::string const& fileName)
	{
		auto hasResource = m_resources.contains(fileName);

		if (!hasResource)
			return nullptr;

		return dynamic_cast<T*>(m_resources[fileName]);
	}

}
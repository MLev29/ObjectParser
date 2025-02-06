#include "ResourceManager.h"

std::mutex objParser::ResourceManager::m_mutex;
objParser::ResourceManager* objParser::ResourceManager::m_instance = nullptr;

objParser::ResourceManager* objParser::ResourceManager::GetInstance(void)
{
	if (!m_instance)
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		if (!m_instance)
			m_instance = new ResourceManager();
	}
	
	return m_instance;
}

void objParser::ResourceManager::Unload(std::string const& fileName)
{
	if (!m_resources.contains(fileName))
		return;

	delete m_resources[fileName];
}

void objParser::ResourceManager::UnloadAll(void)
{
	for (auto& resource : m_resources)
	{
		delete resource.second;
	}
}

void objParser::ResourceManager::Update(Shader* shader)
{
	for (auto& resource : m_resources)
	{
		resource.second->Update(shader);
	}
}

void objParser::ResourceManager::CloseResourceManager(void)
{
	delete m_instance;
}


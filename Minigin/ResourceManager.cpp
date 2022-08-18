#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "SpriteGroup.h"

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file)
{
	if (m_TextureMap.contains(file)) {
		auto texture = m_TextureMap.find(file);
		if (texture->second.use_count() > 0) {
			return texture->second.lock();
		}
		m_TextureMap.erase(file);
	}
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	std::shared_ptr<Texture2D> sharedTexture(std::make_shared<Texture2D>(texture));
	m_TextureMap.insert(std::pair<std::string, std::weak_ptr<Texture2D>>(file, std::weak_ptr<Texture2D>(sharedTexture)));
	return sharedTexture;
}

std::shared_ptr<dae::SpriteGroup> dae::ResourceManager::LoadSpriteGroup(const std::string& spriteGroupName)
{
	if (m_SpriteGroupMap.contains(spriteGroupName)) {
		auto spriteGroup = m_SpriteGroupMap.find(spriteGroupName);
		if (spriteGroup->second.use_count() > 0) {
			return spriteGroup->second.lock();
		}
		m_SpriteGroupMap.erase(spriteGroupName);
	}
	std::shared_ptr<SpriteGroup> sharedSpriteGroup(std::make_shared<SpriteGroup>());
	m_SpriteGroupMap.insert(std::pair<std::string, std::weak_ptr<SpriteGroup>>(spriteGroupName, std::weak_ptr<SpriteGroup>(sharedSpriteGroup)));

	return sharedSpriteGroup;
}


std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}

bool dae::ResourceManager::IsSpriteGroupLoaded(const std::string& spriteGroupName) {
	return m_SpriteGroupMap.contains(spriteGroupName);
}
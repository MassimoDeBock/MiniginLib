#pragma once
#include "Singleton.h"
#include <unordered_map>

namespace dae
{
	class SpriteGroup;
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
		std::shared_ptr<SpriteGroup> LoadSpriteGroup(const std::string& spriteGroupName);
		bool IsSpriteGroupLoaded(const std::string& spriteGroupName);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;

		std::unordered_map < std::string, std::weak_ptr<Texture2D>> m_TextureMap;
		std::unordered_map < std::string, std::weak_ptr<SpriteGroup>> m_SpriteGroupMap;
	};
}

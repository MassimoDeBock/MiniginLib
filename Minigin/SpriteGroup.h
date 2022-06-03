#pragma once
#include <unordered_map>

namespace dae {
	class ImagePart;
	class SpriteGroup
	{
	public:
		SpriteGroup() = default;
		~SpriteGroup() = default;
		std::shared_ptr<ImagePart> GetSprite(const unsigned int index);
		int GetSpritesAmount();
		void InsertSprite(int index, const std::string& filename, const SDL_Rect& snipRect);
		void InsertSprite(int index, const std::string& filename, const glm::vec4& snipRect);
		void InsertSprite(int index, const std::string& filename, float x, float y, float w, float h);
		void InsertSprite(int index, const std::string& filename, int x, int y, int w, int h);
	private:
		std::unordered_map<int, std::shared_ptr<ImagePart>> m_MapOfSprites;
	};
}
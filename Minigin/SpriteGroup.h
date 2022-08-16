#pragma once
#include <unordered_map>
#include <memory>
struct SDL_Rect;

namespace dae {
	class ImagePart;
	class SpriteGroup
	{
	public:
		SpriteGroup() = default;
		~SpriteGroup() = default;
		std::shared_ptr<ImagePart> GetSprite(const unsigned int index);
		int GetSpritesAmount();
		void InsertSprite(int index, const std::string& filename, const SDL_Rect& snipRect, bool mirror = false);
		void InsertSprite(int index, const std::string& filename, float x, float y, float w, float h, bool mirror = false);
		void InsertSprite(int index, const std::string& filename, int x, int y, int w, int h, bool mirror = false);
	private:
		std::unordered_map<int, std::shared_ptr<ImagePart>> m_MapOfSprites;
	};
}
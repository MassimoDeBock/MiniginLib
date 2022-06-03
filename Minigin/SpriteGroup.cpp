#include "MiniginPCH.h"
#include "SpriteGroup.h"
#include "Texture2D.h"
#include "ImagePart.h"

std::shared_ptr<dae::ImagePart> dae::SpriteGroup::GetSprite(const unsigned int index)
{
	return m_MapOfSprites.find(index)->second;
}

int dae::SpriteGroup::GetSpritesAmount()
{
	return m_MapOfSprites.size();
}

void dae::SpriteGroup::InsertSprite(int index, const std::string& filename, const SDL_Rect& snipRect)
{
	if (!m_MapOfSprites.contains(index)) {
		m_MapOfSprites.insert(std::pair<int, std::shared_ptr<ImagePart>>(index, std::make_shared<ImagePart>(filename, snipRect)));
	}
}

void dae::SpriteGroup::InsertSprite(int index, const std::string& filename, const glm::vec4& snipRect)
{
	InsertSprite(index, filename, SDL_Rect(int(snipRect.x), int(snipRect.y), int(snipRect.z), int(snipRect.w)));
}

void dae::SpriteGroup::InsertSprite(int index, const std::string& filename, float x, float y, float w, float h)
{
	InsertSprite(index, filename, SDL_Rect(int(x), int(y), int(w), int(h)));
}

void dae::SpriteGroup::InsertSprite(int index, const std::string& filename, int x, int y, int w, int h)
{
	InsertSprite(index, filename, SDL_Rect(x, y, w, h));
}

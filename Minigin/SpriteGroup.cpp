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
	return int(m_MapOfSprites.size());
}

void dae::SpriteGroup::InsertSprite(int index, const std::string& filename, const SDL_Rect& snipRect, bool mirror)
{
	if (!m_MapOfSprites.contains(index)) {
		std::shared_ptr<ImagePart> imgpart;
		if (mirror) {
			//imgpart = std::make_shared<ImagePart>(filename, SDL_Rect(snipRect.x+ snipRect.w,snipRect.y+ snipRect.h, -snipRect.w, -snipRect.h));
			imgpart = std::make_shared<ImagePart>(filename, snipRect);
		}
		else {
			imgpart = std::make_shared<ImagePart>(filename, snipRect);
		}
		m_MapOfSprites.insert(std::pair<int, std::shared_ptr<ImagePart>>(index, imgpart));
	}
}


void dae::SpriteGroup::InsertSprite(int index, const std::string& filename, float x, float y, float w, float h, bool mirror)
{
	InsertSprite(index, filename, SDL_Rect(int(x), int(y), int(w), int(h)), mirror);
}

void dae::SpriteGroup::InsertSprite(int index, const std::string& filename, int x, int y, int w, int h, bool mirror)
{
	InsertSprite(index, filename, SDL_Rect(x, y, w, h), mirror);
}

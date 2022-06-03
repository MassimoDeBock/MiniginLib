#include "MiniginPCH.h"
#include "ImagePart.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::ImagePart::ImagePart(const std::string& filename, const SDL_Rect& snipRect)
	:m_Texture(ResourceManager::GetInstance().LoadTexture(filename))
	,m_SnipRect(snipRect)
{
	Update();
}

dae::ImagePart::ImagePart(const std::string& filename, const glm::vec4& snipRect)
	:ImagePart(filename, SDL_Rect(int(snipRect.x), int(snipRect.y), int(snipRect.z), int(snipRect.w)))
{
}

dae::ImagePart::ImagePart(const std::string& filename, float x, float y, float w, float h)
	:ImagePart(filename, SDL_Rect(int(x),int(y), int(w), int(h)))
{
}

dae::ImagePart::ImagePart(const std::string& filename, int x, int y, int w, int h)
	: ImagePart(filename, SDL_Rect(x, y, w, h))
{
}

void dae::ImagePart::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	Update();
}

void dae::ImagePart::SetRect(const SDL_Rect& snipRect)
{
	m_SnipRect = snipRect;
}

void dae::ImagePart::SetRect(const glm::vec4& snipRect)
{
	SetRect(SDL_Rect(int(snipRect.x), int(snipRect.y), int(snipRect.z), int(snipRect.w)));
}

void dae::ImagePart::SetRect(float x, float y, float w, float h)
{
	SetRect(SDL_Rect(int(x), int(y), int(w), int(h)));
}

void dae::ImagePart::SetRect(int x, int y, int w, int h)
{
	SetRect(SDL_Rect(x, y, w, h));
}


void dae::ImagePart::Render(float x, float y) const
{
	Renderer::GetInstance().RenderTexture(*m_TexturePart, x, y);
}

//the following function is taken from https://stackoverflow.com/questions/38686927/how-to-get-a-part-of-texture-in-sdl2
void dae::ImagePart::Update()
{
	SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();
	SDL_Texture* result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_SnipRect.w, m_SnipRect.h);
	SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, result);
	SDL_RenderCopy(renderer, m_Texture.get()->GetSDLTexture(), &m_SnipRect, NULL);
	SDL_SetRenderTarget(renderer, NULL);
	m_TexturePart = std::make_unique<Texture2D>(result);
}

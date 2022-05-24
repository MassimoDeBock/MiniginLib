#include "MiniginPCH.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include <SDL_ttf.h>


dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font)
	: TextComponent(text, font, SDL_Color(255, 255, 255))
{

}

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, SDL_Color color)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_TextTexture(nullptr), m_Color(color)
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = m_GameObjectRef->GetAbsoluteTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(SDL_Color color)
{
	m_Color = color;
}

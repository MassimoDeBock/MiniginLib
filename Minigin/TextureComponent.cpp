#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(const std::string& filename)
{
	SetTexture(filename);
}


void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);

}

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Render() const
{
	glm::vec3 rpos = m_GameObjectRef->GetAbsoluteTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, rpos.x, rpos.y);
}
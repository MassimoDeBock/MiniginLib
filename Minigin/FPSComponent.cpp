#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"

dae::FPSComponent::FPSComponent()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	m_textComponent = std::make_unique<TextComponent>("", font);
}

void dae::FPSComponent::Update()
{
	++m_UpdateFrameCounter;
	if (!(m_UpdateFrameCounter < m_UpdateEveryXFrames)) {
		m_UpdateFrameCounter = 0;
		float deltatime = m_GameObjectRef->m_sceneRef->GetDeltaTime();
		int fps = int(float(1 / deltatime));
		std::string text =std::to_string(fps) + " FPS";
		m_textComponent.get()->SetText(text);

		if (fps >50) {
			m_textComponent.get()->SetColor(SDL_Color(0, 220, 0));
		}
		else if (fps > 35) {
			m_textComponent.get()->SetColor(SDL_Color(220, 220, 0));
		}
		else if (fps > 20) {
			m_textComponent.get()->SetColor(SDL_Color(220, 100, 0));
		}
		else {
			m_textComponent.get()->SetColor(SDL_Color(220, 0, 0));
		}

		m_textComponent.get()->Update();
	}
}

void dae::FPSComponent::SetParent(GameObject* parentGameObject) {
	m_GameObjectRef = parentGameObject;
	m_textComponent.get()->SetParent(parentGameObject);
}

void dae::FPSComponent::Render() const
{
	m_textComponent.get()->Render();
}

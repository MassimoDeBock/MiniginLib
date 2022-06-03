#include "MiniginPCH.h"
#include "GameScoreBoardComponent.h"
#include "PeterPepperBrainComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"

dae::GameScoreBoardComponent::GameScoreBoardComponent(const unsigned short playerAmount, const std::string& playerName, const SDL_Color& color0, const SDL_Color& color1, const SDL_Color& color2, const SDL_Color& color3)
	: m_PlayerAmount(playerAmount),
	m_playerName(playerName),
	m_Color{ color0,color1,color2,color3 }
{
}

void dae::GameScoreBoardComponent::OnNotify(const GameObject& gameObject, Event event, int optionalValue)
{
	switch (event)
	{
	case dae::Event::PlayerDied:
		PlayerDied(gameObject);
		break;
	case dae::Event::PointsObtained:
		PointsAdded(gameObject ,optionalValue);
		break;
	default:
		break;
	}
}


void dae::GameScoreBoardComponent::BeginPlay()
{
	for (unsigned short i = 0; i < m_PlayerAmount; ++i) {
		std::string objectName = m_playerName;
		if (i > 0) {
			objectName += std::to_string(i);
		}
		auto temp = m_GameObjectRef->m_sceneRef->GetGameObject(objectName);
		if (temp != nullptr) {
			m_pPlayerObjects[i] = temp;
			m_playerLives[i] = 3;
			temp->GetComponent<PeterPepperBrainComponent>("PeterPepperBrainComponent")->m_Subject.AddObserver(this);
		}
		else {
			m_PlayerAmount = i;
			std::cout << "unsuccessfull player not found, make sure to have a \"" << objectName << "\" or lower the playeramount of GameScoreBoardComponent" << std::endl;
		}
	}
	{
		int offsetMultiplier = 30;
		auto sceneRef = m_GameObjectRef->m_sceneRef;
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
		for (unsigned short i = 0; i < m_PlayerAmount; ++i) {
			auto go = std::make_shared<GameObject>();
			m_pLivesTextComponents[i] = new TextComponent("Lives: " + std::to_string(m_playerLives[i]), font, m_Color[i]);
			go->AddComponent("GameDisplay", m_pLivesTextComponents[i]);
			go->SetParent(m_GameObjectRef);
			go->SetRelativeTransform(0, float(offsetMultiplier * i * 2));
			sceneRef->Add("PlayerLives" + std::to_string(i), go);

			go = std::make_shared<GameObject>();
			m_pPointsTextComponents[i] = new TextComponent("Score: " + std::to_string(m_playerScore[i]), font, m_Color[i]);
			go->AddComponent("GameDisplay", m_pPointsTextComponents[i]);
			go->SetParent(m_GameObjectRef);
			go->SetRelativeTransform(0, float(offsetMultiplier * (i * 2 + 1)));
			sceneRef->Add("PlayerScore" + std::to_string(i), go);
		}
	}
}

void dae::GameScoreBoardComponent::PlayerDied(const GameObject& gameObject)
{
	for (unsigned short i = 0; i < m_PlayerAmount; ++i) {
		if (m_pPlayerObjects[i] != &gameObject) {
			--m_playerLives[i];
			m_pLivesTextComponents[i]->SetText("Lives: " + std::to_string(m_playerLives[i]));
		}
	}
}

void dae::GameScoreBoardComponent::PointsAdded(const GameObject& gameObject, const int addition)
{
	for (unsigned short i = 0; i < m_PlayerAmount; ++i) {
		if (m_pPlayerObjects[i] != &gameObject) {
			m_playerScore[i]+=addition;
			m_pPointsTextComponents[i]->SetText("Score: " + std::to_string(m_playerScore[i]));
		}
	}
}

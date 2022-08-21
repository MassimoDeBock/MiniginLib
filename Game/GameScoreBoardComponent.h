#pragma once
#include "Component.h"
#include "Observer.h"
#define MAX_AMOUNT_OF_PLAYERS 4

namespace dae {
	class TextComponent;
	class GameScoreBoardComponent : public Component, public Observer
	{
	public:
		GameScoreBoardComponent(const unsigned short playerAmount, const std::string& playerName,
			const SDL_Color& color0 = SDL_Color(100, 184, 97),
			const SDL_Color& color1 = SDL_Color(217, 202, 87),
			const SDL_Color& color2 = SDL_Color(217, 139, 87),
			const SDL_Color& color3 = SDL_Color(87, 217, 189)
		);

		virtual void OnNotify(const GameObject& gameObject, Event event, int optionalValue = 0) override;
		void BeginPlay() override;


	private:

		void PlayerDied(const GameObject& gameObject);
		void PointsAdded(const GameObject& gameObject, const int addition);

		const int m_StartLives{ 3 };
		std::string m_playerName;
		GameObject* m_pPlayerObjects[MAX_AMOUNT_OF_PLAYERS]{ nullptr };
		unsigned short m_PlayerAmount;
		TextComponent* m_pLivesTextComponents[MAX_AMOUNT_OF_PLAYERS]{ nullptr };
		TextComponent* m_pPointsTextComponents[MAX_AMOUNT_OF_PLAYERS]{ nullptr };

		int m_playerScore[MAX_AMOUNT_OF_PLAYERS]{};
		int m_playerLives[MAX_AMOUNT_OF_PLAYERS]{};

		SDL_Color m_Color[MAX_AMOUNT_OF_PLAYERS]{};
	};
}
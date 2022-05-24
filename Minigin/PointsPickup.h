#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae {
	class RectColliderComponent;
    class PointsPickup :
        public Component, public Observer
	{
	public:
		PointsPickup(const glm::vec2& size, const int points);
		virtual ~PointsPickup();

		void OnAssign() override;

		void OnNotify(const GameObject& gameObject, Event eventType, int optionalValue = 0) override;

	private:
		void HandleEvents(const GameObject& gameObject, Event eventType, int optionalValue = 0);
		void IsHit(const GameObject& gameObject);
		void SetUseable(const bool newValue );

		RectColliderComponent* m_pRectComponent;
		bool m_Useable{true};
		const int m_Points;
		const glm::vec2 m_Size;
		SDL_Color m_Color{ 25, 255, 25 };
	};
}
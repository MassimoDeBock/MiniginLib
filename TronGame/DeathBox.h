#pragma once
#include "Component.h"
#include "Observer.h"
#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

namespace dae {
	class DeathBox :
		public Component, public Observer
	{
	public:
		DeathBox(const glm::vec2& size);
		virtual ~DeathBox();

		void OnAssign() override;

		void OnNotify(const GameObject& gameObject, Event eventType, int optionalValue = 0) override;

	private:
		void HandleEvents(const GameObject& gameObject, Event eventType, int optionalValue = 0);
		void IsHit(const GameObject& gameObject);

		const glm::vec2 m_Size;
	};

}
#pragma once
#include "Event.h"

namespace dae {
	class RectColliderComponent;
	class GameObject;
	class Observer 
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(const GameObject& gameObject, Event event, int optionalValue = 0) = 0;
		virtual void OnNotifyHitbox(const dae::GameObject& gameObject, RectColliderComponent* other, Event eventType, int optionalValue = 0) = 0;
		virtual void OnNotifyNoReturn(Event eventType, int optionalValue = 0) = 0;
	};
}
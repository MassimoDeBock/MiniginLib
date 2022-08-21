#pragma once
#include "Event.h"

namespace dae {
	class GameObject;
	class Observer 
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(const GameObject& gameObject, Event event, int optionalValue = 0) = 0;
		virtual void OnNotifyNoReturn(Event event, int optionalValue = 0) = 0;
	};
}
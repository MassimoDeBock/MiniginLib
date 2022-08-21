#pragma once
#include <list>
#include "Event.h"

namespace dae {
	class RectColliderComponent;
	class GameObject;
	class Observer;
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const dae::GameObject& gameObject, RectColliderComponent* other, Event event, const int optionalValue = 0);
		void Notify(const GameObject& other, Event event, const int optionalValue = 0);
		void NotifyNoReturn(Event event, const int optionalValue = 0);
	private:
		std::list<Observer*> m_Observers;

	};
}
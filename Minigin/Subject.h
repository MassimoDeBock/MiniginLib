#pragma once
#include <list>
#include "Event.h"

namespace dae {
	class GameObject;
	class Observer;
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(const GameObject& gameObject, Event event, const int optionalValue = 0);
	private:
		std::list<Observer*> m_Observers;

	};
}
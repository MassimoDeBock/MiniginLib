#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	for (std::list<Observer*>::iterator it = m_Observers.begin(); it != m_Observers.end(); ++it) {
		if (*it == observer) {
			m_Observers.erase(it);
		}
	}
}

void dae::Subject::Notify(const GameObject& gameObject, Event event, const int optionalValue)
{
	for (auto const& it : m_Observers) {
		it->OnNotify(gameObject, event, optionalValue);
	}
}

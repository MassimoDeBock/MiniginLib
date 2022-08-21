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

void dae::Subject::Notify(const dae::GameObject& gameObject, RectColliderComponent* other, Event eventType, const int optionalValue)
{
	for (auto const& it : m_Observers) {
		it->OnNotifyHitbox(gameObject,other, eventType, optionalValue);
	}
}

void dae::Subject::Notify(const GameObject& other, Event event, const int optionalValue)
{
	for (auto const& it : m_Observers) {
		it->OnNotify(other, event, optionalValue);
	}
}

void dae::Subject::NotifyNoReturn(Event event, const int optionalValue)
{
	for (auto const& it : m_Observers) {
		it->OnNotifyNoReturn(event, optionalValue);
	}
}


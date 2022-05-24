#include "MiniginPCH.h"
#include "PointsPickup.h"
#include "GameObject.h"
#include "RectColliderComponent.h"
#include "PeterPepperBrainComponent.h"

dae::PointsPickup::PointsPickup(const glm::vec2& size, const int points)
	: m_Size(size), m_Points(points)
{
}

dae::PointsPickup::~PointsPickup()
{
}

void dae::PointsPickup::OnAssign()
{
	m_GameObjectRef->SetTag(Tag::neutral);
	m_pRectComponent = new RectColliderComponent(m_Size);
	m_GameObjectRef->AddComponent<RectColliderComponent>("RectColliderComponent", m_pRectComponent);
	m_pRectComponent->DoVisualise(true);
	m_pRectComponent->SetVisualizeColor(m_Color);

	m_pRectComponent->m_Subject.AddObserver(this);
}

void dae::PointsPickup::OnNotify(const GameObject& gameObject, Event eventType, int optionalValue)
{
	HandleEvents(gameObject, eventType, optionalValue);
}

void dae::PointsPickup::HandleEvents(const GameObject& gameObject, Event eventType, int optionalValue)
{
	optionalValue;
	switch (eventType)
	{
	case dae::Event::Dummy:
		break;
	case dae::Event::PlayerDied:
		IsHit(gameObject);
		break;
	case dae::Event::IsHit:
		IsHit(gameObject);
		break;
	case dae::Event::Hits:
		IsHit(gameObject);
		break;
	default:
		break;
	}
}

void dae::PointsPickup::IsHit(const GameObject& gameObject)
{
	switch (gameObject.GetTag())
	{
	case Tag::friendly:
		if (m_Useable) {
			gameObject.GetComponent<PeterPepperBrainComponent>("PeterPepperBrainComponent")->GetPoints(400);
			SetUseable(false);
		}
		break;
	default:
		break;
	}
}

void dae::PointsPickup::SetUseable(const bool newValue)
{
	m_Useable = newValue;

	if (m_Useable) {
		m_pRectComponent->SetVisualizeColor(SDL_Color(m_Color.r, m_Color.g, m_Color.b));
	}
	else {
		m_pRectComponent->SetVisualizeColor(SDL_Color(m_Color.r/2, m_Color.g/2, m_Color.b/2));
	}
}

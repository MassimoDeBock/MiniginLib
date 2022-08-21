#include "MiniginPCH.h"
#include "DeathBox.h"
#include "GameObject.h"
#include "RectColliderComponent.h"

dae::DeathBox::DeathBox(const glm::vec2& size)
	: m_Size(size)
{
}

dae::DeathBox::~DeathBox()
{
}

void dae::DeathBox::OnAssign()
{
	m_GameObjectRef->SetTag(Tag::enemy);
	RectColliderComponent* rectComponent = new RectColliderComponent(m_Size);
	m_GameObjectRef->AddComponent<RectColliderComponent>("RectColliderComponent", rectComponent);
	rectComponent->DoVisualise(true);
	rectComponent->SetVisualizeColor(SDL_Color(255,0,0));

	rectComponent->m_Subject.AddObserver(this);
}

void dae::DeathBox::OnNotify(const GameObject& gameObject, Event eventType, int optionalValue)
{
	HandleEvents(gameObject, eventType, optionalValue);
}

void dae::DeathBox::HandleEvents(const GameObject& gameObject, Event eventType, int optionalValue)
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

void dae::DeathBox::IsHit(const GameObject& gameObject)
{
	//std::cout << "DeathBox got hit by " ;
	switch (gameObject.GetTag())
	{
	case Tag::friendly:
		//std::cout << "an ally\n";
		break;
	default:
		//std::cout << "a default\n";
		break;
	}
}


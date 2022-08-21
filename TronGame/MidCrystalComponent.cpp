#include "MidCrystalComponent.h"
#include "DeathBox.h"
#include "GameObject.h"
#include "RectColliderComponent.h"
#include <iostream>
#include <GameObject.h>
#include <Scene.h>
#include <Subject.h>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

MidCrystalComponent::MidCrystalComponent(const int x, const int y)
	:m_Size(x,y)
{
}

MidCrystalComponent::~MidCrystalComponent()
{
}

void MidCrystalComponent::OnAssign()
{
	m_GameObjectRef->SetTag(dae::Tag::neutral);
	glm::vec2 offset{ -m_Size.x / 2, -m_Size.x / 2 };

	dae::RectColliderComponent* rectComponent = new dae::RectColliderComponent(m_Size,offset);
	m_GameObjectRef->AddComponent<dae::RectColliderComponent>("RectColliderComponent", rectComponent);
	rectComponent->DoVisualise(true);
	rectComponent->SetVisualizeColor(SDL_Color{ 255,0,0 });

	rectComponent->m_Subject.AddObserver(this);
}

void MidCrystalComponent::OnNotify(const dae::GameObject& gameObject, dae::Event eventType, int optionalValue)
{
	gameObject; eventType; optionalValue;
}

void MidCrystalComponent::OnNotifyHitbox(const dae::GameObject& gameObject, dae::RectColliderComponent* other, dae::Event eventType, int optionalValue)
{
//	HandleEvents(, eventType, optionalValue);
	gameObject;
	other->m_Subject;
	HandleEvents(gameObject ,other, eventType, optionalValue);
}

void MidCrystalComponent::OnNotifyNoReturn(dae::Event eventType, int optionalValue)
{
	eventType;
	optionalValue;
}

void MidCrystalComponent::HandleEvents(const dae::GameObject& gameObject, dae::RectColliderComponent* other, dae::Event eventType, int optionalValue)
{
	gameObject;
	optionalValue;
	switch (eventType)
	{
	case dae::Event::Dummy:
		break;
	case dae::Event::PlayerDied:
		break;
	case dae::Event::IsHit:
		other->m_Subject.NotifyNoReturn(dae::Event::TeleportRandom);
		break;
	case dae::Event::Hits:
		break;
	default:
		break;
	}
}

void MidCrystalComponent::IsHit(const dae::GameObject& gameObject)
{
	std::cout << "midcrystalhit" << std::endl;
	switch (gameObject.GetTag())
	{
	case dae::Tag::friendly:
		//std::cout << "an ally\n";
		break;
	default:
		//std::cout << "a default\n";
		break;
	}
}

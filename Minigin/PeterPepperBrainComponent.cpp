#include "MiniginPCH.h"
#include "PeterPepperBrainComponent.h"
#include "PeterPepperPlayerController.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "RectColliderComponent.h"
#include "Locator.h"
#include "AudioProvider.h"

dae::PeterPepperBrainComponent::PeterPepperBrainComponent(const int playerID)
	: m_PlayerID(playerID)
{
}

dae::PeterPepperBrainComponent::~PeterPepperBrainComponent()
{
}

void dae::PeterPepperBrainComponent::Update()
{
}

void dae::PeterPepperBrainComponent::OnAssign()
{
	m_GameObjectRef->AddComponent<TextureComponent>("TextureComponent", new TextureComponent("Peter_Pepper.png"));
	m_GameObjectRef->AddComponent<PeterPepperPlayerController>("PeterPepperPlayerController", new PeterPepperPlayerController(m_PlayerID));
	m_GameObjectRef->GetComponent<MovementComponent>("MovementComponent")->SetMovementSpeed(Transform(0.5, 0.5, 0));

	RectColliderComponent* pTemp = new RectColliderComponent(glm::vec2(32, 32));
	m_GameObjectRef->AddComponent<RectColliderComponent>("RectColliderComponent", pTemp);
	pTemp->DoVisualise(true);
	m_GameObjectRef->SetTag(Tag::friendly);

	pTemp->m_Subject.AddObserver(this);

}

void dae::PeterPepperBrainComponent::BeginPlay()
{
	m_SpawnLocation = glm::vec2(m_GameObjectRef->GetAbsoluteTransform().GetPosition().x, m_GameObjectRef->GetAbsoluteTransform().GetPosition().y);
}

void dae::PeterPepperBrainComponent::GetPoints(const int value)
{
	m_Subject.Notify(*m_GameObjectRef, Event::PointsObtained, value);
}

void dae::PeterPepperBrainComponent::OnNotify(const GameObject& gameObject, Event eventType, int optionalValue)
{
	HandleEvents(gameObject, eventType, optionalValue);
}

void dae::PeterPepperBrainComponent::HandleEvents(const GameObject& gameObject, Event eventType, int optionalValue)
{
	optionalValue;
	switch (eventType)
	{
	case dae::Event::PlayerDied:
		Dies();
		break;
	case dae::Event::IsHit:
		break;
	case dae::Event::Hits:
		Hits(gameObject);
		break;
	default:
		break;
	}
}

void dae::PeterPepperBrainComponent::Hits(const GameObject& gameObject)
{
	if (gameObject.GetTag() == Tag::enemy) {
		m_Subject.Notify(*m_GameObjectRef, Event::PlayerDied);
		Dies();
	}
}

void dae::PeterPepperBrainComponent::Dies()
{
	Locator::GetAudio().PlaySound(1);
	m_GameObjectRef->SetAbsoluteTransform(Transform(m_SpawnLocation.x, m_SpawnLocation.y));
}

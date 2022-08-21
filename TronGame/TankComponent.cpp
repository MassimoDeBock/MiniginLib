#include "TankComponent.h"
#include <SpriteGroup.h>
#include <ImagePart.h>
#include <Texture2D.h>
#include "ResourceManager.h"
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)
#include <GameObject.h>
#include "TankComponent.h"
#include "MapComponent.h"
#include <Scene.h>
#include <SceneManager.h>
#include "TankMovementComponent.h"
#include <iostream>
#include "TronPlayerController.h"
#include "BulletHandlerComponent.h"
#include "Transform.h"
#include <RectColliderComponent.h>
#include <Locator.h>
#include <AudioProvider.h>

TankComponent::TankComponent(const int playerID, int teamID, int spriteRow)
	: m_SpriteVariationRow(spriteRow)
	, m_PlayerID(playerID)
	, m_TeamID(teamID)
	, m_MovementComponent(nullptr)
{
}

TankComponent::~TankComponent()
{
}

void TankComponent::Update()
{
	float deltaTime = m_GameObjectRef->m_sceneRef->GetDeltaTime();

	if (m_FireRateCD > 0) m_FireRateCD -= deltaTime;
}

void TankComponent::Render() const
{
	glm::vec3 rpos = m_GameObjectRef->GetAbsoluteTransform().GetPosition();


	m_SpriteGroup.get()->GetSprite(int(int(m_MovementComponent->GetMoveDirection()) + m_SpriteVariationRow * 4))->Render(rpos.x - MapComponent::spriteDimension, rpos.y - MapComponent::spriteDimension);
	//m_SpriteGroup.get()->GetSprite(0)->Render(rpos.x - MapComponent::spriteDimension, rpos.y - MapComponent::spriteDimension);

}

void TankComponent::OnAssign()
{
	LoadSprites();

	m_MovementComponent = new TankMovementComponent(m_MoveSpeed);
	m_GameObjectRef->AddComponent<TankMovementComponent>("TankMovementComponent", m_MovementComponent); //const float movementSpeed, std::shared_ptr<MapComponent> mapRef

	m_GameObjectRef->AddComponent<TronPlayerController>("TronPlayerController", new TronPlayerController(m_PlayerID, this, m_MovementComponent));

	m_BulletHandler = m_GameObjectRef->m_sceneRef->GetGameObject("_BulletHandler")->GetComponent<BulletHandlerComponent>("BulletHandlerComponent");

	dae::RectColliderComponent* pTemp = new dae::RectColliderComponent(glm::vec2(64, 64), glm::vec2(-32, -32));
	m_GameObjectRef->AddComponent<dae::RectColliderComponent>("RectColliderComponent", pTemp);
	//pTemp->DoVisualise(true);
	if (m_TeamID == 0) {
		m_GameObjectRef->SetTag(dae::Tag::friendly);
	}
	else {
		m_GameObjectRef->SetTag(dae::Tag::enemy);
	}
	pTemp->m_Subject.AddObserver(this);

	//{
	//	m_MovementComponent = (m_GameObjectRef->GetComponent<MovementComponent>("MovementComponent"));
	//	m_MovementComponent->SetMovementSpeed(Transform(0.5, 0.5, 0));
	//}

	//RectColliderComponent* pTemp = new RectColliderComponent(glm::vec2(32, 32));
	//m_GameObjectRef->AddComponent<RectColliderComponent>("RectColliderComponent", pTemp);
	//pTemp->DoVisualise(true);
	//m_GameObjectRef->SetTag(Tag::friendly);

	//pTemp->m_Subject.AddObserver(this);

}

void TankComponent::BeginPlay()
{
}

void TankComponent::Shoot(dae::Transform direction)
{
	if (!(m_FireRateCD > 0)) {
		dae::Locator::GetAudio().PlaySound(1);
		m_BulletHandler->SpawnBullet(m_TeamID, 0.4f, m_GameObjectRef->GetAbsoluteTransform(), direction, 5);
		m_FireRateCD = m_FireRate;
	}
}

void TankComponent::OnNotify(const dae::GameObject& gameObject, dae::Event tevent, int optionalValue)
{
	gameObject;
	optionalValue;
	tevent;
}

void TankComponent::OnNotifyNoReturn(dae::Event eventType, int optionalValue)
{
	HandleEvents(eventType, optionalValue);
}

void TankComponent::LoadSprites()
{
	if (m_SpriteGroup)return;
	std::string newSpriteGroupName{ "TankSheet" };

	if (dae::ResourceManager::GetInstance().IsSpriteGroupLoaded(newSpriteGroupName)) {

		m_SpriteGroup = dae::ResourceManager::GetInstance().LoadSpriteGroup(newSpriteGroupName);
		return;
	}

	m_SpriteGroup = dae::ResourceManager::GetInstance().LoadSpriteGroup(newSpriteGroupName);
	for (int y = 0; y < 7; ++y) {
		for (int x = 0; x < 4; ++x) {
			m_SpriteGroup->InsertSprite(y * 4 + x, "TankSheet.png", SDL_Rect(MapComponent::spriteDimension * 2 * x, MapComponent::spriteDimension * 2 * y, MapComponent::spriteDimension * 2, MapComponent::spriteDimension * 2));
		}
	}
}

void TankComponent::HandleEvents(dae::Event eventType, int optionalValue)
{
	switch (eventType)
	{
	case dae::Event::IsHit:
		if (optionalValue != m_TeamID) {
			TakeDamage();
		}
		break;
	default:
		break;
	}
}

void TankComponent::TakeDamage(int damage)
{
	m_HP -= damage;
	m_Subject.Notify(*m_GameObjectRef, dae::Event::UpdateHealth, m_HP);
	if (m_HP < 1) {
		Dies();
	}
}

void TankComponent::Dies()
{
	std::cout << "PlayerDied" << std::endl;
}

//newSpriteGroupName = "AITanks";

//if (!bool(dae::ResourceManager::GetInstance().IsSpriteGroupLoaded(newSpriteGroupName))) {
//	std::shared_ptr<dae::SpriteGroup> m_SpriteGroup = dae::ResourceManager::GetInstance().LoadSpriteGroup(newSpriteGroupName);
//	for (int y = 0; y < 4; ++y) {
//		for (int x = 0; x < 4; ++x) {
//			m_SpriteGroup->InsertSprite(y * 4 + x, "AITanks.png", SDL_Rect(MapComponent::spriteDimension * x, MapComponent::spriteDimension * y, MapComponent::spriteDimension, MapComponent::spriteDimension));
//		}
//	}
//}



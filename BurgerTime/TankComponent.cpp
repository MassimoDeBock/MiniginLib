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

TankComponent::TankComponent(const int playerID, int spriteRow)
	: m_SpriteVariationRow(spriteRow)
	, m_PlayerID(playerID)
	, m_MovementComponent(nullptr)
{
}

TankComponent::~TankComponent()
{
}

void TankComponent::Update()
{
}

void TankComponent::Render() const
{
	glm::vec3 rpos = m_GameObjectRef->GetAbsoluteTransform().GetPosition();


	m_SpriteGroup.get()->GetSprite(int(int(m_MovementComponent->GetMoveDirection())+m_SpriteVariationRow*4))->Render(rpos.x - MapComponent::spriteDimension, rpos.y - MapComponent::spriteDimension);
	//m_SpriteGroup.get()->GetSprite(0)->Render(rpos.x - MapComponent::spriteDimension, rpos.y - MapComponent::spriteDimension);

}

void TankComponent::OnAssign()
{
	LoadSprites();

	m_MovementComponent = new TankMovementComponent(m_MoveSpeed);
	m_GameObjectRef->AddComponent<TankMovementComponent>("TankMovementComponent", m_MovementComponent); //const float movementSpeed, std::shared_ptr<MapComponent> mapRef

	m_GameObjectRef->AddComponent<TronPlayerController>("TronPlayerController", new TronPlayerController(m_PlayerID, m_MovementComponent));
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

//newSpriteGroupName = "AITanks";

//if (!bool(dae::ResourceManager::GetInstance().IsSpriteGroupLoaded(newSpriteGroupName))) {
//	std::shared_ptr<dae::SpriteGroup> m_SpriteGroup = dae::ResourceManager::GetInstance().LoadSpriteGroup(newSpriteGroupName);
//	for (int y = 0; y < 4; ++y) {
//		for (int x = 0; x < 4; ++x) {
//			m_SpriteGroup->InsertSprite(y * 4 + x, "AITanks.png", SDL_Rect(MapComponent::spriteDimension * x, MapComponent::spriteDimension * y, MapComponent::spriteDimension, MapComponent::spriteDimension));
//		}
//	}
//}



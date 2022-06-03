#include "MiniginPCH.h"
#include "PeterPepperBrainComponent.h"
#include "PeterPepperPlayerController.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "RectColliderComponent.h"
#include "Locator.h"
#include "AudioProvider.h"
#include "Texture2D.h"
#include "SpriteGroup.h"
#include "ImagePart.h"
#include "ResourceManager.h"
#include "Scene.h"

dae::PeterPepperBrainComponent::PeterPepperBrainComponent(const int playerID)
	: m_PlayerID(playerID)
{
}

dae::PeterPepperBrainComponent::~PeterPepperBrainComponent()
{
}

void dae::PeterPepperBrainComponent::Update()
{
	CalcDirection();
	if (m_isMoving) {
		m_Tick += m_GameObjectRef->m_sceneRef->GetDeltaTime();
		if (!(m_Tick < m_SpriteUpdatePerSecond)) {
			m_Tick -= m_SpriteUpdatePerSecond;
			m_ImgCounter = (++m_ImgCounter) % 3;
		}
	}
}

void dae::PeterPepperBrainComponent::Render() const
{
	glm::vec3 rpos = m_GameObjectRef->GetAbsoluteTransform().GetPosition();
	m_SpriteGroup.get()->GetSprite(int(int(m_CurrentDirection) + m_ImgCounter))->Render(rpos.x, rpos.y);
}

void dae::PeterPepperBrainComponent::OnAssign()
{
	LoadSprites();
	//m_GameObjectRef->AddComponent<TextureComponent>("TextureComponent", new TextureComponent("Peter_Pepper.png"));
	m_GameObjectRef->AddComponent<PeterPepperPlayerController>("PeterPepperPlayerController", new PeterPepperPlayerController(m_PlayerID));

	m_MovementComponent = std::shared_ptr<dae::MovementComponent>(m_GameObjectRef->GetComponent<MovementComponent>("MovementComponent"));
	m_MovementComponent->SetMovementSpeed(Transform(0.5, 0.5, 0));

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

void dae::PeterPepperBrainComponent::CalcDirection()
{
	m_isMoving = true;
	if (m_MovementComponent.get()->GetVelocity().GetPosition().x > 0.1f) {
		m_CurrentDirection = SpritesOrder::Right;
		return;
	}
	if (m_MovementComponent.get()->GetVelocity().GetPosition().x < -0.1f) {
		m_CurrentDirection = SpritesOrder::Left;
		return;
	}
	if (m_MovementComponent.get()->GetVelocity().GetPosition().y > 0.1f) {
		m_CurrentDirection = SpritesOrder::Down;
		return;
	}
	if (m_MovementComponent.get()->GetVelocity().GetPosition().y < -0.1f) {
		m_CurrentDirection = SpritesOrder::Up;
		return;
	}
	m_isMoving = false;
}

void dae::PeterPepperBrainComponent::LoadSprites()
{
	std::string spritesheetname{ "SpriteSheetUpdated.png" };
	if (ResourceManager::GetInstance().IsSpriteGroupLoaded("PeterPepper")) {
		m_SpriteGroup = ResourceManager::GetInstance().LoadSpriteGroup("PeterPepper");
		return;
	}
	m_SpriteGroup = ResourceManager::GetInstance().LoadSpriteGroup("PeterPepper");
	glm::vec2 dimensions{ 32,32 };
	for (int i = 0; i < 3; ++i) {
		m_SpriteGroup->InsertSprite(int(SpritesOrder::Up) +i, spritesheetname,			SDL_Rect(int(dimensions.x) * (6 + i), int(dimensions.y) * 0, int(dimensions.x), int(dimensions.y)), true);
		m_SpriteGroup->InsertSprite(int(SpritesOrder::Left) + i, spritesheetname,		SDL_Rect(int(dimensions.x) * (3 + i), int(dimensions.y) * 0, int(dimensions.x), int(dimensions.y)), true);
		m_SpriteGroup->InsertSprite(int(SpritesOrder::Right) + i, spritesheetname,		SDL_Rect(int(dimensions.x) * (3 + i), int(dimensions.y) * 0, int(dimensions.x), int(dimensions.y)), true);
		m_SpriteGroup->InsertSprite(int(SpritesOrder::Down) + i, spritesheetname,		SDL_Rect(int(dimensions.x) * (0 + i), int(dimensions.y) * 0, int(dimensions.x), int(dimensions.y)), true);
	}
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

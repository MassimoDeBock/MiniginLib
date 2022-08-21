#include <MiniginPCH.h>
#include "BulletHandlerComponent.h"
#include <Scene.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Renderer.h>
#include <iostream>
#include <Locator.h>
#include <AudioProvider.h>
#include <CollisionManager.h>
#include <RectColliderComponent.h>
#include <Tags.h>

BulletHandlerComponent::BulletHandlerComponent()
{
}

BulletHandlerComponent::~BulletHandlerComponent()
{
}

void BulletHandlerComponent::FixedUpdate()
{
	//note: Theres ways that are wayyyy better, since its not a bullet hell it should be fine for now.
	m_TimeStep = m_GameObjectRef->m_sceneRef->GetFixedTimeStep();
	dae::Tag tag{ dae::Tag::friendly };
	for (std::vector<Bullet*>::iterator it = m_Bullets.begin(); it != m_Bullets.end();) {
		HandleBulletMovement(*it);


		if ((*it)->m_OwningTeam == 0) {
			tag = dae::Tag::friendly;
		}
		else {
			tag = dae::Tag::enemy;
		}
		if (m_GameObjectRef->m_sceneRef->m_CollisionManager.CheckCollisionsNoReturn((*it)->m_Position.GetPosition().x - m_BulletSize / 2, (*it)->m_Position.GetPosition().y - m_BulletSize / 2, float(m_BulletSize), float(m_BulletSize), tag ,(*it)->m_OwningTeam)) {
			(*it)->m_Bounces = 0;
		}

		if ((*it)->m_Bounces < 1) {
			it = m_Bullets.erase(it);
		}
		else {
			++it;
		}
	}
}

void BulletHandlerComponent::OnAssign()
{
	m_MapRef = m_GameObjectRef->m_sceneRef->GetGameObject("-Map")->GetComponent<MapComponent>("MapComponent");

	m_Texture = dae::ResourceManager::GetInstance().LoadTexture("bullet.png");

}

void BulletHandlerComponent::Render() const
{
	for (Bullet* i : m_Bullets) {
		dae::Renderer::GetInstance().RenderTexture(*m_Texture.get(), i->m_Position.GetPosition().x - m_BulletSize / 2, i->m_Position.GetPosition().y - m_BulletSize / 2);
	}
}

void BulletHandlerComponent::SpawnBullet(int owningTeam, float movespeed, dae::Transform startPos, const dae::Transform& startVelocity, int maxBounces)
{
	m_Bullets.push_back(new Bullet(startPos, startVelocity, movespeed, owningTeam, maxBounces));
}

void BulletHandlerComponent::HandleBulletMovement(Bullet* bullet)
{

	int colX = int((bullet->m_Position.GetPosition().x - m_MapRef->GetActorLocation().x) / (MapComponent::spriteDimension));
	int rowY = int((bullet->m_Position.GetPosition().y - m_MapRef->GetActorLocation().y) / (MapComponent::spriteDimension));

	//std::cout << colX << "|" << rowY << std::endl;

	if (!(m_MapRef->IsValidTile(colX, rowY))) {
		bullet->m_Bounces = 0;
		return;
	}

	if ((m_MapRef->GetTileValue(colX, rowY) == 1)) {
		bullet->m_Position += bullet->m_MoveVelocity * bullet->m_MoveSpeed * m_TimeStep;
		return;
	}

	glm::vec2 center = m_MapRef->GetTileCenter(colX, rowY);
	glm::vec2 offset = glm::vec2(bullet->m_Position.GetPosition().x, bullet->m_Position.GetPosition().y) - center;


	int wallHit = 0; //0none 1up 2right 3down 4left

	bool xVelCheck = ((bullet->m_MoveVelocity.GetPosition().x > 0) != (offset.x > 0)) && !(abs(bullet->m_MoveVelocity.GetPosition().x) <= 0.01f);
	bool yVelCheck = (bullet->m_MoveVelocity.GetPosition().y > 0) != (offset.y > 0) && !(abs(bullet->m_MoveVelocity.GetPosition().y) <= 0.01f);

	if ((xVelCheck != yVelCheck)) {
		if (xVelCheck) {
			if (abs(offset.x) <= abs(bullet->m_MoveVelocity.GetPosition().x) * bullet->m_MoveSpeed * m_TimeStep) {
				float temp = abs(offset.x) / abs(bullet->m_MoveVelocity.GetPosition().x);
				if ((temp * bullet->m_MoveVelocity.GetPosition().y + offset.y) > 0) {
					wallHit = 3;
				}
				else {
					wallHit = 1;


				}
			}
		}
		else {
			if (abs(offset.y) <= abs(bullet->m_MoveVelocity.GetPosition().y) * bullet->m_MoveSpeed * m_TimeStep) { // <-
				float temp = abs(offset.y) / abs(bullet->m_MoveVelocity.GetPosition().y);
				if (temp * bullet->m_MoveVelocity.GetPosition().x + offset.x > 0) {
					wallHit = 2;
				}
				else {
					wallHit = 4;
				}
			}
		}
	}
	else if ((xVelCheck == 1) && (yVelCheck == 1)) {   //multiple possible collisions		0none 1up 2right 3down 4left
		if (abs(offset.x) < abs(offset.y)) {
			if (abs(offset.x) <= abs(bullet->m_MoveVelocity.GetPosition().x) * bullet->m_MoveSpeed * m_TimeStep) {
				float temp = abs(offset.x) / abs(bullet->m_MoveVelocity.GetPosition().x);
				if ((temp * bullet->m_MoveVelocity.GetPosition().y + offset.y) >= 0) {
					if (m_MapRef->GetTileValue(colX, rowY + 1) == 0) wallHit = 3;
				//	else if(m_MapRef->GetTileValue(colX, rowY - 1) == 0) wallHit = 1;
				}
				else {
					if (m_MapRef->GetTileValue(colX, rowY - 1) == 0) wallHit = 1;
					//else if (m_MapRef->GetTileValue(colX, rowY + 1) == 0) wallHit = 3;
				}
			}
			if (wallHit == 0) {
				if (abs(offset.y) <= abs(bullet->m_MoveVelocity.GetPosition().y) * bullet->m_MoveSpeed * m_TimeStep) {
					float temp = abs(offset.y) / abs(bullet->m_MoveVelocity.GetPosition().y);
					if (temp * bullet->m_MoveVelocity.GetPosition().x + offset.x >= 0) {
						if (m_MapRef->GetTileValue(colX + 1, rowY) == 0) wallHit = 2;
					//	else if(m_MapRef->GetTileValue(colX - 1, rowY) == 0) wallHit = 4;
					}
					else {
						if (m_MapRef->GetTileValue(colX - 1, rowY) == 0) wallHit = 4;
					//	else if (m_MapRef->GetTileValue(colX + 1, rowY) == 0) wallHit = 2;
					}
				}
			}
		}
		else {
			if (abs(offset.y) <= abs(bullet->m_MoveVelocity.GetPosition().y) * bullet->m_MoveSpeed * m_TimeStep) {
				float temp = abs(offset.y) / abs(bullet->m_MoveVelocity.GetPosition().y);
				if (temp * bullet->m_MoveVelocity.GetPosition().x + offset.x >= 0) {
					if (m_MapRef->GetTileValue(colX + 1, rowY) == 0) wallHit = 2;
					//else 	if (m_MapRef->GetTileValue(colX - 1, rowY) == 0) wallHit = 4;
				}
				else {
					if (m_MapRef->GetTileValue(colX - 1, rowY) == 0) wallHit = 4;
					//else if (m_MapRef->GetTileValue(colX + 1, rowY) == 0) wallHit = 2;
				}
			}
			if (wallHit == 0) {
				if (abs(offset.x) <= abs(bullet->m_MoveVelocity.GetPosition().x) * bullet->m_MoveSpeed * m_TimeStep) {
					float temp = abs(offset.x) / abs(bullet->m_MoveVelocity.GetPosition().x);
					if ((temp * bullet->m_MoveVelocity.GetPosition().y + offset.y) >= 0) {
						if (m_MapRef->GetTileValue(colX, rowY + 1) == 0) wallHit = 3;
						//else if (m_MapRef->GetTileValue(colX, rowY - 1) == 0) wallHit = 1;
					}
					else {
						if (m_MapRef->GetTileValue(colX, rowY - 1) == 0) wallHit = 1;
						//else if (m_MapRef->GetTileValue(colX, rowY + 1) == 0) wallHit = 3;
					}
				}
			}
		}
	}


	switch (wallHit) //0none 1up 2right 3down 4left
	{
	case 0:
		//bullet->m_Position += bullet->m_MoveVelocity * bullet->m_MoveSpeed * m_TimeStep;
		break;
	case 1:
		if (m_MapRef->GetTileValue(colX, rowY - 1) == 0) {
			bullet->m_MoveVelocity.SetPosition(-bullet->m_MoveVelocity.GetPosition().x, bullet->m_MoveVelocity.GetPosition().y, 0);
			dae::Locator::GetAudio().PlaySound(2);
			--(bullet->m_Bounces);
		}
		break;
	case 2:
		if (m_MapRef->GetTileValue(colX + 1, rowY) == 0) {
			bullet->m_MoveVelocity.SetPosition(bullet->m_MoveVelocity.GetPosition().x, -bullet->m_MoveVelocity.GetPosition().y, 0);
			dae::Locator::GetAudio().PlaySound(2);
			--(bullet->m_Bounces);
		}
		break;
	case 3:
		if (m_MapRef->GetTileValue(colX, rowY + 1) == 0) {
			bullet->m_MoveVelocity.SetPosition(-bullet->m_MoveVelocity.GetPosition().x, bullet->m_MoveVelocity.GetPosition().y, 0);
			dae::Locator::GetAudio().PlaySound(2);
			--(bullet->m_Bounces);
		}
		break;
	case 4:
		if (m_MapRef->GetTileValue(colX - 1, rowY) == 0) {
			bullet->m_MoveVelocity.SetPosition(bullet->m_MoveVelocity.GetPosition().x, -bullet->m_MoveVelocity.GetPosition().y, 0);
			dae::Locator::GetAudio().PlaySound(2);
			--(bullet->m_Bounces);
		}
		break;
	default:
		break;
	}
	bullet->m_Position += bullet->m_MoveVelocity * bullet->m_MoveSpeed * m_TimeStep;
}

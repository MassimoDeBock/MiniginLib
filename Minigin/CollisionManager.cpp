#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

dae::CollisionManager::CollisionManager()
{
}

void dae::CollisionManager::AddRectCollider(RectColliderComponent* collider)
{
	m_Colliders.push_back(collider);
	//m_Colliders.push_back(collider);
}

void dae::CollisionManager::RemoveRectCollider(RectColliderComponent* collider)
{
	for (std::list<RectColliderComponent*>::iterator it = m_Colliders.begin(); it != m_Colliders.end(); ++it) {
		if (*it == collider) {
			m_Colliders.erase(it);
		}
	}
}

void dae::CollisionManager::CheckCollisions(RectColliderComponent* collider)
{
	for (auto const& it : m_Colliders) {
		if (collider->IsOverlapping(it)) {
			collider->Hits(it);
			it->IsHit(collider);
		}
	}
}

bool dae::CollisionManager::CheckCollisionsNoReturn(float x, float y, float w, float h, int optionalValue)
{
	bool didHit{ false };
	for (auto const& it : m_Colliders) {
		if (it->IsOverlapping(x, y, w, h)) {
			it->IsHitNoReturn(optionalValue);
			didHit = true;
		}
	}
	return didHit;
}

bool dae::CollisionManager::CheckCollisionsNoReturn(float x, float y, float w, float h, dae::Tag tag, int optionalValue)
{
	bool didHit{ false };
	for (auto const& it : m_Colliders) {
		if (it->IsOverlapping(x, y, w, h)) {
			it->IsHitNoReturn(optionalValue);
			if (it->GetGameObject()->GetTag()!=tag) {
				didHit = true;
			}
		}
	}
	return didHit;
}


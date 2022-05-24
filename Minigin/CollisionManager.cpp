#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "RectColliderComponent.h"

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

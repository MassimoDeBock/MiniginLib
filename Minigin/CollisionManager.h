#pragma once
#include <list>

namespace dae {
	class RectColliderComponent;
	class CollisionManager
	{
	public:
		CollisionManager();

		void AddRectCollider(RectColliderComponent* collider);
		void RemoveRectCollider(RectColliderComponent* collider);

		void CheckCollisions(RectColliderComponent* collider);
	private:
		std::list<RectColliderComponent*> m_Colliders;
	};

}
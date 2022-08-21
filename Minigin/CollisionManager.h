#pragma once
#include <list>
#include "Tags.h"

namespace dae {
	class RectColliderComponent;
	class CollisionManager
	{
	public:
		CollisionManager();

		void AddRectCollider(RectColliderComponent* collider);
		void RemoveRectCollider(RectColliderComponent* collider);

		void CheckCollisions(RectColliderComponent* collider);
		bool CheckCollisionsNoReturn(float x, float y, float w, float h, int optionalValue = 0);
		bool CheckCollisionsNoReturn(float x, float y, float w, float h,Tag, int optionalValue = 0);

	private:
		std::list<RectColliderComponent*> m_Colliders;
	};

}
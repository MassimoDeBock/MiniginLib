#pragma once
#pragma once
#include <Component.h>
#include <memory>
#include "MapComponent.h"

#include <Transform.h>

namespace dae {
	class Texture2D;
	class Transform;
}
class BulletHandlerComponent :
	public dae::Component
{
public:
	BulletHandlerComponent();
	~BulletHandlerComponent();

	void FixedUpdate() override;
	void OnAssign() override;

	void Render()const override;

	void SpawnBullet(int owningTeam, float movespeed, dae::Transform startPos, const dae::Transform& startVelocity, int maxBounces);



private:

	struct Bullet {
		Bullet(dae::Transform startPos ,dae::Transform startVelocity, float movespeed, int owningteam, int bounces) :m_Position(startPos), m_MoveVelocity(startVelocity), m_MoveSpeed(movespeed), m_OwningTeam(owningteam), m_Bounces(bounces) {}
		dae::Transform m_Position{ 0,0 };
		dae::Transform m_MoveVelocity{ 0,0 };
		float m_MoveSpeed{ 0.2f };
		const int m_OwningTeam;
		int m_Bounces;
	};

	void HandleBulletMovement(Bullet* bullet);
	float m_TimeStep{ 0.0f };

	std::shared_ptr<dae::Texture2D> m_Texture;
	std::vector<Bullet*> m_Bullets{};
	MapComponent* m_MapRef{nullptr};
	int m_BulletSize{16};
};


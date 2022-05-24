#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae {
	class MovementComponent : public Component
	{
	public:
		MovementComponent(const Transform& movementSpeed = Transform(1,1,1));
		virtual ~MovementComponent();
		void Update() override;
		void Render() const override;
		void FixedUpdate() override;

		void SetMovementSpeed(const Transform& movementSpeed);
		Transform GetMovementSpeed();
		void SetVelocity(const Transform& newVelocity);
		void SetVelocity_X(const float value);
		void SetVelocity_Y(const float value);
		void SetVelocity_Z(const float value);
		Transform GetVelocity() const;
	private:
		Transform m_MovementSpeed;
		Transform m_Velocity;
	};
}
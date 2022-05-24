#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "Scene.h"

dae::MovementComponent::MovementComponent(const Transform& movementSpeed)
	:m_MovementSpeed(movementSpeed)
{
}

dae::MovementComponent::~MovementComponent()
{
}

void dae::MovementComponent::Update()
{
}

void dae::MovementComponent::Render() const
{
}

void dae::MovementComponent::FixedUpdate() {
	m_GameObjectRef->AddTransform((m_MovementSpeed * m_Velocity) * m_GameObjectRef->m_sceneRef->GetFixedTimeStep());
}

void dae::MovementComponent::SetMovementSpeed(const Transform& movementSpeed)
{
	m_MovementSpeed = movementSpeed;
}

dae::Transform dae::MovementComponent::GetMovementSpeed()
{
	return m_MovementSpeed;
}

void dae::MovementComponent::SetVelocity(const Transform& newVelocity)
{
	m_Velocity = newVelocity;
}

void dae::MovementComponent::SetVelocity_X(const float value)
{
	m_Velocity.SetPosition(value, m_Velocity.GetPosition().y, m_Velocity.GetPosition().z);
}

void dae::MovementComponent::SetVelocity_Y(const float value)
{
	m_Velocity.SetPosition(m_Velocity.GetPosition().x, value, m_Velocity.GetPosition().z);
}

void dae::MovementComponent::SetVelocity_Z(const float value)
{
	m_Velocity.SetPosition(m_Velocity.GetPosition().x, m_Velocity.GetPosition().y, value);
}

dae::Transform dae::MovementComponent::GetVelocity() const
{
	return m_Velocity;
}

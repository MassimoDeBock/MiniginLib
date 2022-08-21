#include "TankMovementComponent.h"
#include "MapComponent.h"
#include <GameObject.h>
#include "Scene.h"
#include <iostream>

TankMovementComponent::TankMovementComponent(const float movementSpeed)
	:m_MoveSpeed(movementSpeed)
{
}

void TankMovementComponent::FixedUpdate()
{
	//	std::cout << "begin fixedUpdate tankmovecomp" << std::endl;
	RegulateMovement();

	//std::cout << m_ColX << "[" << m_CellOffset.GetPosition().x << "] | | " << m_RowY << "[" << m_CellOffset.GetPosition().y << "]" << std::endl;

	m_ColX += int(m_CellOffset.GetPosition().x) / (MapComponent::spriteDimension/2);
	m_RowY += int(m_CellOffset.GetPosition().y) / (MapComponent::spriteDimension/2);


	if (m_CellOffset.GetPosition().x >= MapComponent::spriteDimension / 2) {
	//	std::cout << "wee" << std::endl;
		m_CellOffset.SetPosition(m_CellOffset.GetPosition().x - MapComponent::spriteDimension, m_CellOffset.GetPosition().y, 0.0f);
	}
	else if (m_CellOffset.GetPosition().x <= -MapComponent::spriteDimension / 2) {
//		std::cout << "wee" << std::endl;
		m_CellOffset.SetPosition(m_CellOffset.GetPosition().x + MapComponent::spriteDimension, m_CellOffset.GetPosition().y, 0.0f);
	}
	if (m_CellOffset.GetPosition().y >= MapComponent::spriteDimension / 2) {
		m_CellOffset.SetPosition(m_CellOffset.GetPosition().x, m_CellOffset.GetPosition().y - MapComponent::spriteDimension, 0.0f);
	}
	else if (m_CellOffset.GetPosition().y <= -MapComponent::spriteDimension / 2) {
		m_CellOffset.SetPosition(m_CellOffset.GetPosition().x, m_CellOffset.GetPosition().y + MapComponent::spriteDimension, 0.0f);
	}


	//m_GameObjectRef->SetAbsoluteTransform((m_MovementSpeed * m_Velocity) * m_GameObjectRef->m_sceneRef->GetFixedTimeStep());
	m_GameObjectRef->SetAbsoluteTransform((float(m_ColX) + 0.5f) * MapComponent::spriteDimension + m_CellOffset.GetPosition().x + m_MapRef->GetActorLocation().x, (float(m_RowY) + 0.5f) * MapComponent::spriteDimension + m_CellOffset.GetPosition().y + m_MapRef->GetActorLocation().x);
	//	std::cout << "end fixedUpdate tankmovecomp" << std::endl;
}

void TankMovementComponent::OnAssign()
{
	m_MapRef = m_GameObjectRef->m_sceneRef->GetGameObject("-Map")->GetComponent<MapComponent>("MapComponent");
	CalcGridPos();
	FixedUpdate();
}

dae::Transform TankMovementComponent::GetVelocity() const
{
	return m_Velocity;
}

TankMovementComponent::MoveDirection TankMovementComponent::GetMoveDirection()const
{
	return m_MoveDirection;
}

void TankMovementComponent::SetVelocity(const dae::Transform& newVelocity)
{
	m_Velocity = newVelocity;
}

void TankMovementComponent::CalcGridPos()
{
	m_ColX = int(m_GameObjectRef->GetAbsoluteTransform().GetPosition().x - m_MapRef->GetActorLocation().x) / (MapComponent::spriteDimension);
	m_RowY = int(m_GameObjectRef->GetAbsoluteTransform().GetPosition().y - m_MapRef->GetActorLocation().y) / (MapComponent::spriteDimension);
}

void TankMovementComponent::RegulateMovement()
{
	//m_CellOffset += m_Velocity;
	const int fixTreshHold{ MapComponent::spriteDimension }; //max value is spriteDimension/2, anything above means you'll move through regardless


	if (m_Velocity.GetPosition().x > 0.3f) {
		if ((m_MapRef->GetDisplayValue(m_ColX, m_RowY) & int(MapComponent::DirectionValues::Right) || m_CellOffset.GetPosition().x < 0)) {
			if (abs(m_CellOffset.GetPosition().y) < 1) {
				m_CellOffset.SetPosition(m_CellOffset.GetPosition().x + m_Velocity.GetPosition().x * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f, 0.0f);
				m_MoveDirection = MoveDirection::Right;
			}
			else {
				if (abs(m_CellOffset.GetPosition().y) < fixTreshHold) {
					if (abs(m_CellOffset.GetPosition().y) < m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep()) {
						m_CellOffset.SetPosition(0.0f, 0.0f, 0.0f);
					}
					else if (m_CellOffset.GetPosition().y < 0) {
						m_MoveDirection = MoveDirection::Down;
						m_CellOffset.SetPosition(0.0f, m_CellOffset.GetPosition().y + abs(m_Velocity.GetPosition().x) * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f);
					}
					else {
						m_MoveDirection = MoveDirection::Up;
						m_CellOffset.SetPosition(0.0f, m_CellOffset.GetPosition().y - abs(m_Velocity.GetPosition().x) * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f);
					}
				}
				else {
					m_MoveDirection = MoveDirection::Right;
				}
			}
		}
	}
	else if (m_Velocity.GetPosition().y > 0.3f) {
		if ((m_MapRef->GetDisplayValue(m_ColX, m_RowY) & int(MapComponent::DirectionValues::Down))|| m_CellOffset.GetPosition().y < 0 ) {
			if (abs(m_CellOffset.GetPosition().x) < 1) {
				m_CellOffset.SetPosition(0.0f, m_CellOffset.GetPosition().y + m_Velocity.GetPosition().y * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f);
				m_MoveDirection = MoveDirection::Down;
			}
			else {
				if (abs(m_CellOffset.GetPosition().x) < fixTreshHold) {
					if (abs(m_CellOffset.GetPosition().x) < m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep()) {
						m_CellOffset.SetPosition(0.0f, 0.0f, 0.0f);
					}
					else if (m_CellOffset.GetPosition().x < 0) {
						m_MoveDirection = MoveDirection::Right;
						m_CellOffset.SetPosition(m_CellOffset.GetPosition().x + abs(m_Velocity.GetPosition().y) * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f, 0.0f);
					}
					else {
						m_MoveDirection = MoveDirection::Left;
						m_CellOffset.SetPosition(m_CellOffset.GetPosition().x - abs(m_Velocity.GetPosition().y) * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f, 0.0f);
					}
				}
				else {
					m_MoveDirection = MoveDirection::Right;
				}
			}
		}
	}
	else if (m_Velocity.GetPosition().x < -0.3f) {
		if ((m_MapRef->GetDisplayValue(m_ColX, m_RowY) & int(MapComponent::DirectionValues::Left)) || m_CellOffset.GetPosition().x > 0) {
			if (abs(m_CellOffset.GetPosition().y) < 1) {
				m_CellOffset.SetPosition(m_CellOffset.GetPosition().x + m_Velocity.GetPosition().x * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f, 0.0f);
				m_MoveDirection = MoveDirection::Left;
			}
			else {
				if (abs(m_CellOffset.GetPosition().y) < fixTreshHold) {
					if (abs(m_CellOffset.GetPosition().y) < m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep()) {
						m_CellOffset.SetPosition(0.0f, 0.0f, 0.0f);
					}
					else if (m_CellOffset.GetPosition().y < 0) {
						m_MoveDirection = MoveDirection::Down;
						m_CellOffset.SetPosition(0.0f, m_CellOffset.GetPosition().y + abs(m_Velocity.GetPosition().x) * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f);
					}
					else {
						m_MoveDirection = MoveDirection::Up;
						m_CellOffset.SetPosition(0.0f, m_CellOffset.GetPosition().y - abs(m_Velocity.GetPosition().x) * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f);
					}
				}
				else {
					m_MoveDirection = MoveDirection::Left;
				}
			}
		}
	}
	else if (m_Velocity.GetPosition().y < -0.3f) {
		if ((m_MapRef->GetDisplayValue(m_ColX, m_RowY) & int(MapComponent::DirectionValues::Up)) || m_CellOffset.GetPosition().y > 0) {
			if (abs(m_CellOffset.GetPosition().x) < 1) {
				m_CellOffset.SetPosition(0.0f, m_CellOffset.GetPosition().y + m_Velocity.GetPosition().y * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f);
				m_MoveDirection = MoveDirection::Up;
			}
			else {
				if (abs(m_CellOffset.GetPosition().x) < fixTreshHold) {
					if (abs(m_CellOffset.GetPosition().x) < m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep()) {
						m_CellOffset.SetPosition(0.0f, 0.0f, 0.0f);
					}
					else if (m_CellOffset.GetPosition().x < 0) {
						m_MoveDirection = MoveDirection::Right;
						m_CellOffset.SetPosition(m_CellOffset.GetPosition().x + abs(m_Velocity.GetPosition().y) * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f, 0.0f);
					}
					else {
						m_MoveDirection = MoveDirection::Left;
						m_CellOffset.SetPosition(m_CellOffset.GetPosition().x - abs(m_Velocity.GetPosition().y) * m_MoveSpeed * m_GameObjectRef->m_sceneRef->GetFixedTimeStep(), 0.0f, 0.0f);
					}
				}
				else {
					m_MoveDirection = MoveDirection::Up;
				}
			}
		}
	}
}

#include "MiniginPCH.h"
#include "TronPlayerController.h"
#include <GameObject.h>
#include "TankMovementComponent.h"
#include "TankComponent.h"
#include "InputManager.h"
#include <memory>
#include <iostream>

//#pragma warning(push, 0)
//#include <glm/glm.hpp>
//#include <SDL.h>
//#pragma warning (pop)

TronPlayerController::TronPlayerController(const int playerID, TankComponent* tankComponent, TankMovementComponent* movementComponent)
	: BasePlayerController(playerID)
	, m_MovementComponent(movementComponent)
	, m_TankComponent(tankComponent)
{
}

TronPlayerController::~TronPlayerController()
{
}

void TronPlayerController::Update()
{
	glm::vec2 temp = m_Inputmanager.GetControllerSingularNormalizeLeftThumbDirections(GetPlayerID());
	m_MovementComponent->SetVelocity(dae::Transform(temp.x, -temp.y));
	temp = m_Inputmanager.GetControllerNormalizedRightThumbDirections(GetPlayerID());
	if (abs(temp.x) > 0 || abs(temp.y) > 0) {
		m_TankComponent->Shoot(dae::Transform(temp.x, -temp.y));
	}

}

void TronPlayerController::OnAssign()
{
}

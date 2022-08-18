#include "MiniginPCH.h"
#include "TronPlayerController.h"
#include <GameObject.h>
#include "TankMovementComponent.h"
#include "InputManager.h"
#include <memory>

//#pragma warning(push, 0)
//#include <glm/glm.hpp>
//#include <SDL.h>
//#pragma warning (pop)

TronPlayerController::TronPlayerController(const int playerID, TankMovementComponent* movementComponent)
	: BasePlayerController(playerID)
	, m_MovementComponent(movementComponent)
{
}

TronPlayerController::~TronPlayerController()
{
}

void TronPlayerController::Update()
{
	glm::vec2 temp = m_Inputmanager.GetControllerSingularNormalizeLeftThumbDirections(GetPlayerID());
	m_MovementComponent->SetVelocity(dae::Transform(temp.x, -temp.y));
}

void TronPlayerController::OnAssign()
{
}

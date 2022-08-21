#include "MiniginPCH.h"
#include "PeterPepperPlayerController.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "InputManager.h"

dae::PeterPepperPlayerController::PeterPepperPlayerController(const int playerID)
	:BasePlayerController(playerID)
{
}

dae::PeterPepperPlayerController::~PeterPepperPlayerController()
{
}

void dae::PeterPepperPlayerController::Update()
{
	glm::vec2 temp = m_Inputmanager.GetControllerSingularNormalizeLeftThumbDirections(GetPlayerID());
	m_MovementComponent->SetVelocity(Transform(temp.x, -temp.y));
}

void dae::PeterPepperPlayerController::OnAssign()
{
	m_MovementComponent = new MovementComponent();
	m_GameObjectRef->AddComponent("MovementComponent", m_MovementComponent);



}

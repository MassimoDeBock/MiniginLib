#include "MiniginPCH.h"
#include "BasePlayerController.h"
#include "InputManager.h"

int dae::BasePlayerController::GetPlayerID()
{
    return m_PlayerID;
}

dae::BasePlayerController::BasePlayerController(const int playerID)
    : m_PlayerID(playerID),
    m_Inputmanager(InputManager::GetInstance())
{
}

dae::BasePlayerController::~BasePlayerController()
{
}

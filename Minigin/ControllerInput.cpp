#include "MiniginPCH.h"
#include "ControllerInput.h"
#include "CommandList.h"


struct dae::ControllerInput::Controller_Impl
{
	dae::ControllerInput::Controller_Impl(int controllerIndex)
		: m_ControllerIndex{controllerIndex}
		, commandList(std::make_unique<CommandList>(m_ControllerIndex))
	{
	}
	int m_ControllerIndex;
	std::unique_ptr<CommandList> commandList;
};


dae::ControllerInput::ControllerInput(int controllerIndex)
{
	pCtrlImpl = std::make_unique<Controller_Impl>(Controller_Impl(controllerIndex));
}

void dae::ControllerInput::AddCommandsToController(ControllerButton buttonID, ButtonStates state, Command* command)
{
	switch (state)
	{
	case dae::ButtonStates::Pressed:
		pCtrlImpl->commandList.get()->AddPressedCommand(buttonID, command);
		break;
	case dae::ButtonStates::Down:
		pCtrlImpl->commandList.get()->AddDownCommand(buttonID, command);
		break;
	case dae::ButtonStates::Released:
		pCtrlImpl->commandList.get()->AddReleasedCommand(buttonID, command);
		break;
	case dae::ButtonStates::Up:
		pCtrlImpl->commandList.get()->AddUpCommand(buttonID, command);
		break;
	default:
		break;
	}
}

void dae::ControllerInput::OverrideCommands(ControllerButton buttonID, ButtonStates state, Command* command)
{
	RemoveCommandsFromController(buttonID, state);
	AddCommandsToController(buttonID, state, command);
}

void dae::ControllerInput::RemoveCommandsFromController(ControllerButton buttonID, ButtonStates state)
{
	switch (state)
	{
	case dae::ButtonStates::Pressed:
		pCtrlImpl->commandList->RemovePressedCommand(buttonID);
		break;
	case dae::ButtonStates::Down:
		pCtrlImpl->commandList->RemoveDownCommand(buttonID);
		break;
	case dae::ButtonStates::Released:
		pCtrlImpl->commandList->RemoveReleasedCommand(buttonID);
		break;
	case dae::ButtonStates::Up:
		pCtrlImpl->commandList->RemoveUpCommand(buttonID);
		break;
	default:
		break;
	}
}

void dae::ControllerInput::ProcessInput()
{
	pCtrlImpl->commandList->ProcessInput();
}

void dae::ControllerInput::HandleInput()
{
	pCtrlImpl->commandList->HandleInput();
}

void dae::ControllerInput::CheckConnection()
{
	pCtrlImpl->commandList->CheckConnection();
}

bool dae::ControllerInput::IsConnected() const
{
	pCtrlImpl->commandList->IsConnected();
	return false;
}

int dae::ControllerInput::GetControllerID() const
{
	return pCtrlImpl->m_ControllerIndex;
}

glm::vec2 dae::ControllerInput::GetControllerLeftThumbDirections() const
{
	return pCtrlImpl->commandList->GetControllerLeftThumbDirections();
}

glm::vec2 dae::ControllerInput::GetControllerRightThumbDirections() const
{
	return pCtrlImpl->commandList->GetControllerRightThumbDirections();
}

glm::vec2 dae::ControllerInput::GetControllerNormalizedLeftThumbDirections() const
{
	return pCtrlImpl->commandList->GetControllerNormalizedLeftThumbDirections();
}

glm::vec2 dae::ControllerInput::GetControllerNormalizedRightThumbDirections() const
{
	return pCtrlImpl->commandList->GetControllerNormalizedRightThumbDirections();
}

glm::vec2 dae::ControllerInput::GetControllerSingularNormalizeLeftThumbDirections() const
{
	return pCtrlImpl->commandList->GetControllerSingularNormalizeLeftThumbDirections();
}

glm::vec2 dae::ControllerInput::GetControllerSingularNormalizeRightThumbDirections() const
{
	return pCtrlImpl->commandList->GetControllerSingularNormalizeRightThumbDirections();
}

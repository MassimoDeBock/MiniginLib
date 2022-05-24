#include "MiniginPCH.h"
#include "ControllerInput.h"
#include "CommandList.h"


struct dae::ControllerInput::Controller_Impl
{
	dae::ControllerInput::Controller_Impl()
	{
	}

	std::unique_ptr<CommandList> commandList;
};


dae::ControllerInput::ControllerInput(int controllerIndex)
	: m_ControllerIndex{ controllerIndex }
{
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

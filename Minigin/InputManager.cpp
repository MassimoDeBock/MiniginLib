#include "MiniginPCH.h"
#include "InputManager.h"
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")
#include <Windows.h>
#include <iostream>
#include "Command.h"
#include <Xinput.h>
#include "CommandList.h"
#include <vector>

struct dae::InputManager::Impl
{
	dae::InputManager::Impl()
	{
		for (unsigned int i = 0; i < XUSER_MAX_COUNT; ++i) {
			commandList.push_back(new CommandList());
			commandList.at(i)->SetUserNumber(i);
		}
	}
	
	~Impl() {
		for (auto it = std::begin(commandList); it != std::end(commandList); ++it) {
			delete* it;
		}
	}
	std::vector<CommandList*> commandList;
};



void dae::InputManager::AddCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state, Command* command)
{
	switch (state)
	{
	case dae::ButtonStates::Pressed:
		pimpl->commandList.at(controllerNumber)->AddPressedCommand(buttonID, command);
		break;
	case dae::ButtonStates::Down:
		pimpl->commandList.at(controllerNumber)->AddDownCommand(buttonID, command);
		break;
	case dae::ButtonStates::Released:
		pimpl->commandList.at(controllerNumber)->AddReleasedCommand(buttonID, command);
		break;
	case dae::ButtonStates::Up:
		pimpl->commandList.at(controllerNumber)->AddUpCommand(buttonID, command);
		break;
	default:
		break;
	}

}

void dae::InputManager::SwapCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state, Command* command)
{
	RemoveCommandsFromController(controllerNumber, buttonID, state);
	AddCommandsToController(controllerNumber, buttonID, state, command);
}

void dae::InputManager::RemoveCommandsFromController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state)
{
	switch (state)
	{
	case dae::ButtonStates::Pressed:
		pimpl->commandList.at(controllerNumber)->RemovePressedCommand(buttonID);
		break;
	case dae::ButtonStates::Down:
		pimpl->commandList.at(controllerNumber)->RemoveDownCommand(buttonID);
		break;
	case dae::ButtonStates::Released:
		pimpl->commandList.at(controllerNumber)->RemoveReleasedCommand(buttonID);
		break;
	case dae::ButtonStates::Up:
		pimpl->commandList.at(controllerNumber)->RemoveUpCommand(buttonID);
		break;
	default:
		break;
	}
}


dae::InputManager::InputManager()
	: pimpl(new Impl())
{}

dae::InputManager::~InputManager()
{
}



bool dae::InputManager::ProcessInput()
{	
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		pimpl->commandList.at(i)->ProcessInput();
	}
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}
	HandleInput();

	return true;
}

bool dae::InputManager::HandleInput()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		pimpl->commandList.at(i)->HandleInput();

	}
	return true;
}

void dae::InputManager::CheckConnections()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
		// Simply get the state of the controller from XInput.
		pimpl->commandList.at(i)->CheckConnection();
	}
}

glm::vec2 dae::InputManager::GetControllerLeftThumbDirections(unsigned int controllerNumber) const
{
	return pimpl->commandList.at(controllerNumber)->GetControllerLeftThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerRightThumbDirections(unsigned int controllerNumber) const
{
	return pimpl->commandList.at(controllerNumber)->GetControllerRightThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerNormalizedLeftThumbDirections(unsigned int controllerNumber) const
{
	return pimpl->commandList.at(controllerNumber)->GetControllerNormalizedLeftThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerNormalizedRightThumbDirections(unsigned int controllerNumber) const
{
	return pimpl->commandList.at(controllerNumber)->GetControllerNormalizedRightThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerSingularNormalizeLeftThumbDirections(unsigned int controllerNumber) const
{
	return pimpl->commandList.at(controllerNumber)->GetControllerSingularNormalizeLeftThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerSingularNormalizeRightThumbDirections(unsigned int controllerNumber) const
{
	return pimpl->commandList.at(controllerNumber)->GetControllerSingularNormalizeRightThumbDirections();
}

bool dae::InputManager::IsControllerNumberConnected(unsigned int controllerNumber) const
{
	return pimpl->commandList.at(controllerNumber)->IsConnected();
}

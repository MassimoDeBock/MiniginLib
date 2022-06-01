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
#include "Input_API.h"
#include "ControllerInput.h"
#include "KeyboardInput.h"
#include <unordered_map>

struct dae::InputManager::Impl
{
	dae::InputManager::Impl()
	{
	}

	~Impl() {
		for (auto it : inputList) {
			delete it.second;
		}
	}
	std::unordered_map<int, Input_API*> inputList;
};

void dae::InputManager::AddCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state, Command* command)
{
	auto search = pimpl->inputList.find(controllerNumber);
	if (search == pimpl->inputList.end()) {
		std::cout << "tried to add a command to a non existing controller, forgot to initialize it?" << std::endl;
		return;
	}
	ControllerInput* ctrlInput = dynamic_cast<ControllerInput*>(pimpl->inputList.find(controllerNumber)->second);
	if (ctrlInput == nullptr) {
		std::cout << "tried to add a command to a non existing controller, forgot to initialize it?" << std::endl;
	}
	ctrlInput->AddCommandsToController(buttonID, state, command);
}

void dae::InputManager::SwapCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state, Command* command)
{
	RemoveCommandsFromController(controllerNumber, buttonID, state);
	AddCommandsToController(controllerNumber, buttonID, state, command);
}

void dae::InputManager::RemoveCommandsFromController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state)
{
	if (nullptr == pimpl->inputList.at(controllerNumber)) {
		std::cout << "tried to remove a command to a non existing controller, forgot to initialize it?" << std::endl;
		return;
	}
	ControllerInput* ctrlInput = dynamic_cast<ControllerInput*>(pimpl->inputList.find(controllerNumber)->second);
	if (ctrlInput == nullptr) {
		std::cout << "tried to remove a command to a non existing controller, forgot to initialize it?" << std::endl;
	}
	ctrlInput->RemoveCommandsFromController(buttonID, state);
}



dae::InputManager::InputManager()
	: pimpl(new Impl())
{
	std::cout << "loadInputManager" << std::endl;
}

dae::InputManager::~InputManager()
{
}

void dae::InputManager::Initialize()
{
	pimpl = std::make_unique<Impl>(Impl());
}

void dae::InputManager::AddControllerInput(unsigned int userID, unsigned int inputID)
{
	if (inputID >= m_MaxUserCount) return;
	if (userID >= m_MaxUserCount) return;
	pimpl->inputList.insert(std::pair<int, Input_API*>(userID, new ControllerInput(inputID)));
}

void dae::InputManager::AddKeyboardInput(unsigned int userID)
{
	if (userID >= m_MaxUserCount) return;
	pimpl->inputList.insert(std::pair<int, Input_API*>(userID, new KeyboardInput()));
	//pimpl->inputList.insert(std::pair<int, Input_API*>(inputID, new ControllerInput(inputID)));
}


bool dae::InputManager::ProcessInput()
{

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYUP:
		{
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				return false;
			}
			break;
		}
		default:
			break;
		}
	}
	for (auto& itController : pimpl->inputList) {
		itController.second->ProcessInput();
	}
	HandleInput();

	return true;
}

bool dae::InputManager::HandleInput()
{
	for (auto& itController : pimpl->inputList) {
		itController.second->HandleInput();
	}
	return true;
}

void dae::InputManager::CheckConnections()
{
	for (auto& itController : pimpl->inputList) {
		// Simply get the state of the controller from XInput.
		itController.second->CheckConnection();
	}
}

glm::vec2 dae::InputManager::GetControllerLeftThumbDirections(unsigned int controllerNumber) const
{
	auto search = pimpl->inputList.find(controllerNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerLeftThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerRightThumbDirections(unsigned int controllerNumber) const
{
	auto search = pimpl->inputList.find(controllerNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerRightThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerNormalizedLeftThumbDirections(unsigned int controllerNumber) const
{
	auto search = pimpl->inputList.find(controllerNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerNormalizedLeftThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerNormalizedRightThumbDirections(unsigned int controllerNumber) const
{
	auto search = pimpl->inputList.find(controllerNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerNormalizedRightThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerSingularNormalizeLeftThumbDirections(unsigned int controllerNumber) const
{
	auto search = pimpl->inputList.find(controllerNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerSingularNormalizeLeftThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerSingularNormalizeRightThumbDirections(unsigned int controllerNumber) const
{
	auto search = pimpl->inputList.find(controllerNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerSingularNormalizeRightThumbDirections();
}

bool dae::InputManager::IsControllerNumberConnected(unsigned int controllerNumber) const
{
	auto search = pimpl->inputList.find(controllerNumber);
	if (search == pimpl->inputList.end()) {
		return false;
	}
	return search->second->IsConnected();
}
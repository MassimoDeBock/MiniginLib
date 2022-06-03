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
		for (auto &it : inputList) {
			delete it.second;
		}
	}
	std::unordered_map<int, Input_API*> inputList;
};

void dae::InputManager::AddCommandsToController(unsigned int UserNumber, ControllerButton buttonID, ButtonStates state, Command* command)
{
	auto search = pimpl->inputList.find(UserNumber);
	if (search == pimpl->inputList.end()) {
		std::cout << "tried to add a command to a non existing controller, forgot to initialize it?" << std::endl;
		return;
	}
	ControllerInput* ctrlInput = dynamic_cast<ControllerInput*>(pimpl->inputList.find(UserNumber)->second);
	if (ctrlInput == nullptr) {
		std::cout << "tried to add a command to a non existing controller, might be a keyboard?" << std::endl;
	}
	ctrlInput->AddCommandsToController(buttonID, state, command);
}

void dae::InputManager::SwapCommandsToController(unsigned int UserNumber, ControllerButton buttonID, ButtonStates state, Command* command)
{
	RemoveCommandsFromController(UserNumber, buttonID, state);
	AddCommandsToController(UserNumber, buttonID, state, command);
}

void dae::InputManager::RemoveCommandsFromController(unsigned int UserNumber, ControllerButton buttonID, ButtonStates state)
{
	if (nullptr == pimpl->inputList.at(UserNumber)) {
		std::cout << "tried to remove a command to a non existing controller, forgot to initialize it?" << std::endl;
		return;
	}
	ControllerInput* ctrlInput = dynamic_cast<ControllerInput*>(pimpl->inputList.find(UserNumber)->second);
	if (ctrlInput == nullptr) {
		std::cout << "tried to remove a command to a non existing controller, might be a keyboard?" << std::endl;
	}
	ctrlInput->RemoveCommandsFromController(buttonID, state);
}
#pragma warning(push)
#pragma warning( disable : 26812 )
void dae::InputManager::AddCommandsToKeyboard(unsigned int UserNumber, SDL_Scancode buttonCode, ButtonStates state, Command* command)
{
	auto search = pimpl->inputList.find(UserNumber);
	if (search == pimpl->inputList.end()) {
		std::cout << "tried to add a command to a non existing keyboard, forgot to initialize it?" << std::endl;
		return;
	}
	KeyboardInput* ctrlInput = dynamic_cast<KeyboardInput*>(pimpl->inputList.find(UserNumber)->second);
	if (ctrlInput == nullptr) {
		std::cout << "tried to add a command to a non existing keyboard, might be a controller?" << std::endl;
	}
	ctrlInput->AddCommandsToKeyboard(buttonCode, state, command);
}

void dae::InputManager::SwapCommandsToKeyboard(unsigned int UserNumber, SDL_Scancode buttonCode, ButtonStates state, Command* command)
{
	RemoveCommandsFromKeyboard(UserNumber, buttonCode, state);
	AddCommandsToKeyboard(UserNumber, buttonCode, state, command);
}

void dae::InputManager::RemoveCommandsFromKeyboard(unsigned int UserNumber, SDL_Scancode buttonCode, ButtonStates state)
{
	if (nullptr == pimpl->inputList.at(UserNumber)) {
		std::cout << "tried to remove a command to a non existing keyboard, forgot to initialize it?" << std::endl;
		return;
	}
	KeyboardInput* ctrlInput = dynamic_cast<KeyboardInput*>(pimpl->inputList.find(UserNumber)->second);
	if (ctrlInput == nullptr) {
		std::cout << "tried to remove a command to a non existing keyboard, might be a controller?" << std::endl;
	}
	ctrlInput->RemoveCommandsFromKeyboard(buttonCode, state);
}
#pragma warning(pop)


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

bool dae::InputManager::AddControllerInput(unsigned int userID, unsigned int inputID)
{
	if (inputID >= m_MaxUserCount) return false;
	if (userID >= m_MaxUserCount) return false;
	if (pimpl->inputList.contains(userID)) return false;
	pimpl->inputList.insert(std::pair<int, Input_API*>(userID, new ControllerInput(inputID)));
	return true;
}

bool dae::InputManager::AddKeyboardInput(unsigned int userID)
{
	if (userID >= m_MaxUserCount) return false;
	if (pimpl->inputList.contains(userID)) return false;
	pimpl->inputList.insert(std::pair<int, Input_API*>(userID, new KeyboardInput()));
	return true;
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

glm::vec2 dae::InputManager::GetControllerLeftThumbDirections(unsigned int UserNumber) const
{
	auto search = pimpl->inputList.find(UserNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerLeftThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerRightThumbDirections(unsigned int UserNumber) const
{
	auto search = pimpl->inputList.find(UserNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerRightThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerNormalizedLeftThumbDirections(unsigned int UserNumber) const
{
	auto search = pimpl->inputList.find(UserNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerNormalizedLeftThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerNormalizedRightThumbDirections(unsigned int UserNumber) const
{
	auto search = pimpl->inputList.find(UserNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerNormalizedRightThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerSingularNormalizeLeftThumbDirections(unsigned int UserNumber) const
{
	auto search = pimpl->inputList.find(UserNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerSingularNormalizeLeftThumbDirections();
}

glm::vec2 dae::InputManager::GetControllerSingularNormalizeRightThumbDirections(unsigned int UserNumber) const
{
	auto search = pimpl->inputList.find(UserNumber);
	if (search == pimpl->inputList.end()) {
		return glm::vec2(0, 0);
	}
	return search->second->GetControllerSingularNormalizeRightThumbDirections();
}

bool dae::InputManager::IsControllerNumberConnected(unsigned int UserNumber) const
{
	auto search = pimpl->inputList.find(UserNumber);
	if (search == pimpl->inputList.end()) {
		return false;
	}
	return search->second->IsConnected();
}
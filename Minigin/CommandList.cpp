#include "MiniginPCH.h"
#include "CommandList.h"
#include <memory>
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")
#include <Windows.h>
#include <Xinput.h>
#include <iostream>

struct dae::CommandList::Controller {
	dae::CommandList::Controller() {

	}

	~Controller() {
	}

	bool isConnected{ false };
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_State{};
};


dae::CommandList::CommandList()
	: m_Controller(new Controller())
{
}

dae::CommandList::~CommandList()
{
	for (auto& it : m_PressedCommands) {
		delete it.second;
	}
	for (auto& it : m_DownCommands) {
		delete it.second;
	}
	for (auto& it : m_ReleasedCommands) {
		delete it.second;
	}
	for (auto& it : m_UpCommands) {
		delete it.second;
	}

}

void dae::CommandList::CheckConnection()
{
	DWORD dwResult;
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	dwResult = XInputGetState(m_UserNumber, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		if (!m_Controller->isConnected) {
			m_Controller->isConnected = true;
			std::cout << "Controller \"" << m_UserNumber << "\" just got connected\n";
		}
	}
	else
	{
		// Controller is not connected
	}
}

void dae::CommandList::SetUserNumber(unsigned int num)
{
	m_UserNumber = num;
}

void dae::CommandList::CheckPressedCommand()
{
	for (auto& it : m_PressedCommands) {
		if (IsPressed(it.first)) {
			it.second->Execute();
		}
	}

}

void dae::CommandList::CheckDownCommand()
{
	for (auto& it : m_DownCommands) {
		if (IsDown(it.first)) {
			it.second->Execute();
		}
	}
}

void dae::CommandList::CheckReleasedCommand()
{
	for (auto& it : m_ReleasedCommands) {
		if (IsReleased(it.first)) {
			it.second->Execute();
		}
	}
}

void dae::CommandList::CheckUpCommand()
{
	for (auto& it : m_UpCommands) {
		if (IsUp(it.first)) {
			it.second->Execute();
		}
	}
}

void dae::CommandList::ProcessInput()
{
	if (m_Controller->isConnected) {
		DWORD dwResult;
		XINPUT_STATE tempState{};
		ZeroMemory(&tempState, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(m_UserNumber, &tempState);

		if (dwResult == ERROR_SUCCESS)
		{
			// Controller is connected
			//std::cout << "Controller is connected\n";
		}
		else
		{
			// Controller is not connected
			m_Controller->isConnected = false;
			std::cout << "Controller  \"" << m_UserNumber << "\" just got disconnected\n";
		}
		m_Controller->m_PreviousState = m_Controller->m_State;
		m_Controller->m_State = tempState;
	}
}

void dae::CommandList::HandleInput()
{
	if (m_Controller->isConnected) {
		CheckPressedCommand();
		CheckDownCommand();
		CheckReleasedCommand();
		CheckUpCommand();
	}
}

bool dae::CommandList::IsConnected() const
{
	return m_Controller->isConnected;
}

bool dae::CommandList::IsPressed(ControllerButton button) const
{
	if (!(DWORD(m_Controller->m_PreviousState.Gamepad.wButtons) & DWORD(button)) && (DWORD(m_Controller->m_State.Gamepad.wButtons) & DWORD(button))) {
		return true;
	}
	return false;
}

bool dae::CommandList::IsDown(ControllerButton button) const
{
	if ((DWORD(m_Controller->m_State.Gamepad.wButtons) & DWORD(button))) {
		return true;
	}
	return false;
}

bool dae::CommandList::IsReleased(ControllerButton button) const
{
	if ((DWORD(m_Controller->m_PreviousState.Gamepad.wButtons) & DWORD(button)) && !(DWORD(m_Controller->m_State.Gamepad.wButtons) & DWORD(button))) {
		return true;
	}
	return false;
}

bool dae::CommandList::IsUp(ControllerButton button) const
{
	if (!(DWORD(m_Controller->m_State.Gamepad.wButtons) & DWORD(button))) {
		return true;
	}
	return false;
}

glm::vec2 dae::CommandList::GetControllerLeftThumbDirections() const
{
	return glm::vec2(
		m_Controller.get()->m_State.Gamepad.sThumbLX,
		m_Controller.get()->m_State.Gamepad.sThumbLY);
}

glm::vec2 dae::CommandList::GetControllerRightThumbDirections() const
{
	return glm::vec2(
		m_Controller.get()->m_State.Gamepad.sThumbRX,
		m_Controller.get()->m_State.Gamepad.sThumbRY);
}

glm::vec2 dae::CommandList::GetControllerNormalizedLeftThumbDirections() const
{
	_XINPUT_GAMEPAD thumbstick = m_Controller.get()->m_State.Gamepad;
	glm::vec2 temp(0, 0);
	if (thumbstick.sThumbLX > THUMBSTICKTHRESHHOLD) {
		temp.x = 1;
	}
	else if (thumbstick.sThumbLX < -THUMBSTICKTHRESHHOLD) {
		temp.x = -1;
	}

	if (thumbstick.sThumbLY > THUMBSTICKTHRESHHOLD) {
		temp.y = 1;
	}
	else if (thumbstick.sThumbLY < -THUMBSTICKTHRESHHOLD) {
		temp.y = -1;
	}
	return temp;
}

glm::vec2 dae::CommandList::GetControllerNormalizedRightThumbDirections() const
{
	_XINPUT_GAMEPAD thumbstick = m_Controller.get()->m_State.Gamepad;
	glm::vec2 temp(0, 0);
	if (thumbstick.sThumbRX > THUMBSTICKTHRESHHOLD) {
		temp.x = 1;
	}
	else if (thumbstick.sThumbRX < -THUMBSTICKTHRESHHOLD) {
		temp.x = -1;
	}

	if (thumbstick.sThumbRY > THUMBSTICKTHRESHHOLD) {
		temp.y = 1;
	}
	else if (thumbstick.sThumbRY < -THUMBSTICKTHRESHHOLD) {
		temp.y = -1;
	}
	return temp;
}

glm::vec2 dae::CommandList::GetControllerSingularNormalizeLeftThumbDirections() const
{
	_XINPUT_GAMEPAD thumbstick = m_Controller.get()->m_State.Gamepad;
	glm::vec2 temp(0, 0);
	if (abs(thumbstick.sThumbLX) > abs(thumbstick.sThumbLY)) {
		if (thumbstick.sThumbLX > THUMBSTICKTHRESHHOLD) {
			temp.x = 1;
		}
		else if (thumbstick.sThumbLX < -THUMBSTICKTHRESHHOLD) {
			temp.x = -1;
		}
	}
	else {
		if (thumbstick.sThumbLY > THUMBSTICKTHRESHHOLD) {
			temp.y = 1;
		}
		else if (thumbstick.sThumbLY < -THUMBSTICKTHRESHHOLD) {
			temp.y = -1;
		}
	}
	return temp;
}

glm::vec2 dae::CommandList::GetControllerSingularNormalizeRightThumbDirections() const
{
	_XINPUT_GAMEPAD thumbstick = m_Controller.get()->m_State.Gamepad;
	glm::vec2 temp(0, 0);
	if (abs(thumbstick.sThumbRX) > abs(thumbstick.sThumbRY)) {
		if (thumbstick.sThumbRX > THUMBSTICKTHRESHHOLD) {
			temp.x = 1;
		}
		else if (thumbstick.sThumbRX < -THUMBSTICKTHRESHHOLD) {
			temp.x = -1;
		}
	}
	else {
		if (thumbstick.sThumbRY > THUMBSTICKTHRESHHOLD) {
			temp.y = 1;
		}
		else if (thumbstick.sThumbRY < -THUMBSTICKTHRESHHOLD) {
			temp.y = -1;
		}
	}
	return temp;
}

void dae::CommandList::AddPressedCommand(ControllerButton buttonID, Command* command)
{
	m_PressedCommands.insert(std::make_pair(buttonID, command));

}

void dae::CommandList::RemovePressedCommand(ControllerButton buttonID)
{
	if (m_PressedCommands.find(buttonID) == m_PressedCommands.end()) return;
	delete m_PressedCommands.at(buttonID);
	m_PressedCommands.erase(buttonID);
}

void dae::CommandList::AddDownCommand(ControllerButton buttonID, Command* command)
{
	m_DownCommands.insert(std::make_pair(buttonID, command));

}

void dae::CommandList::RemoveDownCommand(ControllerButton buttonID)
{
	if (m_DownCommands.find(buttonID) == m_DownCommands.end()) return;
	delete m_DownCommands.at(buttonID);
	m_DownCommands.erase(buttonID);
}

void dae::CommandList::AddReleasedCommand(ControllerButton buttonID, Command* command)
{
	m_ReleasedCommands.insert(std::make_pair(buttonID, command));

}

void dae::CommandList::RemoveReleasedCommand(ControllerButton buttonID)
{
	if (m_ReleasedCommands.find(buttonID) == m_ReleasedCommands.end()) return;
	delete m_ReleasedCommands.at(buttonID);
	m_ReleasedCommands.erase(buttonID);
}

void dae::CommandList::AddUpCommand(ControllerButton buttonID, Command* command)
{
	m_UpCommands.insert(std::make_pair(buttonID, command));

}

void dae::CommandList::RemoveUpCommand(ControllerButton buttonID)
{
	if (m_UpCommands.find(buttonID) == m_UpCommands.end()) return;
	delete m_UpCommands.at(buttonID);
	m_UpCommands.erase(buttonID);
}


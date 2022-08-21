#include "MiniginPCH.h"
#include "KeyboardInput.h"
#include <unordered_map>
#include "InputManager.h"

#pragma warning(push)
#pragma warning( disable : 26812 )
struct dae::KeyboardInput::Keyboard_Impl
{
	dae::KeyboardInput::Keyboard_Impl()
	{
	}
	SDL_Scancode m_LJoystickKeys[4]{ SDL_SCANCODE_W,	SDL_SCANCODE_A,		SDL_SCANCODE_S,		SDL_SCANCODE_D };
	unsigned int m_LJoystickOldState{};
	SDL_Scancode m_RJoystickKeys[4]{ SDL_SCANCODE_UP,	SDL_SCANCODE_LEFT,	SDL_SCANCODE_DOWN,	SDL_SCANCODE_RIGHT };
	unsigned int m_RJoystickOldState{};

	std::unordered_map<SDL_Scancode, std::pair<bool, Command*>> m_PressedCommands;
	std::unordered_map<SDL_Scancode, Command*> m_DownCommands;
	std::unordered_map<SDL_Scancode, std::pair<bool, Command*>> m_ReleasedCommands;
	std::unordered_map<SDL_Scancode, Command*> m_UpCommands;
	int m_ControllerIndex = -1;
};


dae::KeyboardInput::KeyboardInput()
{
	pKeyboardImpl = std::make_unique<Keyboard_Impl>(Keyboard_Impl());
}

dae::KeyboardInput::~KeyboardInput()
{
	for (auto& it : pKeyboardImpl->m_PressedCommands) {
		delete it.second.second;
	}
	for (auto& it : pKeyboardImpl->m_DownCommands) {
		delete it.second;
	}
	for (auto& it : pKeyboardImpl->m_ReleasedCommands) {
		delete it.second.second;
	}
	for (auto& it : pKeyboardImpl->m_UpCommands) {
		delete it.second;
	}

}

void dae::KeyboardInput::AddCommandsToKeyboard(SDL_Scancode buttonID, ButtonStates state, Command* command)
{
	switch (state)
	{
	case dae::ButtonStates::Pressed:
		pKeyboardImpl->m_PressedCommands.insert(std::make_pair(buttonID, std::make_pair(false, command)));
		break;
	case dae::ButtonStates::Down:
		pKeyboardImpl->m_DownCommands.insert(std::make_pair(buttonID, command));
		break;
	case dae::ButtonStates::Released:
		pKeyboardImpl->m_ReleasedCommands.insert(std::make_pair(buttonID, std::make_pair(false, command)));
		break;
	case dae::ButtonStates::Up:
		pKeyboardImpl->m_UpCommands.insert(std::make_pair(buttonID, command));
		break;
	default:
		break;
	}
}

void dae::KeyboardInput::OverrideCommands(SDL_Scancode buttonID, ButtonStates state, Command* command)
{
	RemoveCommandsFromKeyboard(buttonID, state);
	AddCommandsToKeyboard(buttonID, state, command);
}

void dae::KeyboardInput::RemoveCommandsFromKeyboard(SDL_Scancode buttonID, ButtonStates state)
{
	switch (state)
	{
	case dae::ButtonStates::Pressed:
		if (pKeyboardImpl->m_PressedCommands.find(buttonID) == pKeyboardImpl->m_PressedCommands.end()) return;
		delete pKeyboardImpl->m_PressedCommands.at(buttonID).second;
		pKeyboardImpl->m_PressedCommands.erase(buttonID);
		break;
	case dae::ButtonStates::Down:
		if (pKeyboardImpl->m_DownCommands.find(buttonID) == pKeyboardImpl->m_DownCommands.end()) return;
		delete pKeyboardImpl->m_DownCommands.at(buttonID);
		pKeyboardImpl->m_DownCommands.erase(buttonID);
		break;
	case dae::ButtonStates::Released:
		if (pKeyboardImpl->m_ReleasedCommands.find(buttonID) == pKeyboardImpl->m_ReleasedCommands.end()) return;
		delete pKeyboardImpl->m_ReleasedCommands.at(buttonID).second;
		pKeyboardImpl->m_ReleasedCommands.erase(buttonID);
		break;
	case dae::ButtonStates::Up:
		if (pKeyboardImpl->m_UpCommands.find(buttonID) == pKeyboardImpl->m_UpCommands.end()) return;
		delete pKeyboardImpl->m_UpCommands.at(buttonID);
		pKeyboardImpl->m_UpCommands.erase(buttonID);
		break;
	default:
		break;
	}
}




int dae::KeyboardInput::GetControllerID() const
{
	return pKeyboardImpl->m_ControllerIndex;
}

void dae::KeyboardInput::HandleInput()
{
	CheckPressedCommand();
	CheckDownCommand();
	CheckReleasedCommand();
	CheckUpCommand();
}


void dae::KeyboardInput::setFakeLJoystick(SDL_Scancode positiveY, SDL_Scancode negativeX, SDL_Scancode negativeY, SDL_Scancode positiveX)
{
	pKeyboardImpl->m_LJoystickKeys[0] = positiveY;
	pKeyboardImpl->m_LJoystickKeys[1] = negativeX;
	pKeyboardImpl->m_LJoystickKeys[2] = negativeY;
	pKeyboardImpl->m_LJoystickKeys[3] = positiveX;
}

void dae::KeyboardInput::setFakeRJoystick(SDL_Scancode positiveY, SDL_Scancode negativeX, SDL_Scancode negativeY, SDL_Scancode positiveX)
{
	pKeyboardImpl->m_RJoystickKeys[0] = positiveY;
	pKeyboardImpl->m_RJoystickKeys[1] = negativeX;
	pKeyboardImpl->m_RJoystickKeys[2] = negativeY;
	pKeyboardImpl->m_RJoystickKeys[3] = positiveX;
}


glm::vec2 dae::KeyboardInput::GetControllerLeftThumbDirections() const
{
	SDL_Event event{};
	glm::vec2 temp;
	if ((pKeyboardImpl->m_LJoystickKeys[0] == event.key.keysym.sym) != (pKeyboardImpl->m_LJoystickKeys[2] == event.key.keysym.sym)) {
		if (pKeyboardImpl->m_LJoystickKeys[0] == event.key.keysym.sym) {
			temp.y = 1;
		}
		else {
			temp.y = -1;
		}
	}
	if ((pKeyboardImpl->m_LJoystickKeys[3] == event.key.keysym.sym) != (pKeyboardImpl->m_LJoystickKeys[1] == event.key.keysym.sym)) {
		if (pKeyboardImpl->m_LJoystickKeys[3] == event.key.keysym.sym) {
			temp.x = 1;
		}
		else {
			temp.x = -1;
		}
	}

	return temp;
}

glm::vec2 dae::KeyboardInput::GetControllerRightThumbDirections() const
{
	SDL_Event event{};
	glm::vec2 temp;
	if ((pKeyboardImpl->m_RJoystickKeys[0] == event.key.keysym.sym) != (pKeyboardImpl->m_RJoystickKeys[2] == event.key.keysym.sym)) {
		if (pKeyboardImpl->m_RJoystickKeys[0] == event.key.keysym.sym) {
			temp.y = 1;
		}
		else {
			temp.y = -1;
		}
	}
	if ((pKeyboardImpl->m_RJoystickKeys[3] == event.key.keysym.sym) != (pKeyboardImpl->m_RJoystickKeys[1] == event.key.keysym.sym)) {
		if (pKeyboardImpl->m_RJoystickKeys[3] == event.key.keysym.sym) {
			temp.x = 1;
		}
		else {
			temp.x = -1;
		}
	}

	return temp;
}

glm::vec2 dae::KeyboardInput::GetControllerNormalizedLeftThumbDirections() const
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	glm::vec2 temp;
	if (state[pKeyboardImpl->m_LJoystickKeys[0]] != state[pKeyboardImpl->m_LJoystickKeys[2]]) {
		if (state[pKeyboardImpl->m_LJoystickKeys[0]]) {
			temp.y = 1;
		}
		else {
			temp.y = -1;
		}
	}
	if (state[pKeyboardImpl->m_LJoystickKeys[3]] != state[pKeyboardImpl->m_LJoystickKeys[1]]) {
		if (state[pKeyboardImpl->m_LJoystickKeys[3]]) {
			temp.x = 1;
		}
		else {
			temp.x = -1;
		}
	}

	return temp;
}

glm::vec2 dae::KeyboardInput::GetControllerNormalizedRightThumbDirections() const
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	glm::vec2 temp;
	if (state[pKeyboardImpl->m_RJoystickKeys[0]] != state[pKeyboardImpl->m_RJoystickKeys[2]]) {
		if (state[pKeyboardImpl->m_RJoystickKeys[0]]) {
			temp.y = 1;
		}
		else {
			temp.y = -1;
		}
	}
	if (state[pKeyboardImpl->m_RJoystickKeys[3]] != state[pKeyboardImpl->m_RJoystickKeys[1]]) {
		if (state[pKeyboardImpl->m_RJoystickKeys[3]]) {
			temp.x = 1;
		}
		else {
			temp.x = -1;
		}
	}

	return temp;
}

glm::vec2 dae::KeyboardInput::GetControllerSingularNormalizeLeftThumbDirections() const
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	unsigned int input{ 0 };
	for (int i = 0; i < 4; ++i) {
		if (state[pKeyboardImpl->m_LJoystickKeys[i]]) {
			input = input | int(pow(2.0, double(i)));
		}
	}
	//std::cout << input 
	//	<< "|" << (input & PositiveY) << "| "
	//	<< "|" << (input & NegativeX) << "| "
	//	<< "|" << (input & NegativeY) << "| "
	//	<< "|" << (input & PositiveX) << "| "
	//	<<   std::endl;
	glm::vec2 temp;
	if (bool(input & NegativeX) != bool(input & PositiveX)) {
		if (bool(input & PositiveY) == bool(input & NegativeY)) {
			if (input & PositiveX) {
				temp.x = 1;
			}
			else {
				temp.x = -1;
			}
		}
		else {
			input ^= pKeyboardImpl->m_LJoystickOldState;
			switch (input)
			{
			case PositiveX:
				temp.x = 1;
				break;
			case NegativeX:
				temp.x = -1;
				break;
			case PositiveY:
				temp.y = 1;
				break;
			case NegativeY:
				temp.y = -1;
				break;
			default:
				break;
			}
			input = input | IsConflict;
		}
	}
	else {
		if (bool(input & PositiveY) != bool(input & NegativeY)) {
			if (input & PositiveY) {
				temp.y = 1;
			}
			else {
				temp.y = -1;
			}
		}
	}

	if (!bool(input & IsConflict)) {
		pKeyboardImpl->m_LJoystickOldState = input;
	}
	return temp;
}

glm::vec2 dae::KeyboardInput::GetControllerSingularNormalizeRightThumbDirections() const
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	unsigned int input{ 0 };
	for (int i = 0; i < 4; ++i) {
		if (state[pKeyboardImpl->m_RJoystickKeys[i]]) {
			input = input | int(pow(2.0, double(i)));
		}
	}
	glm::vec2 temp;
	if (bool(input & NegativeX) != bool(input & PositiveX)) {
		if (bool(input & PositiveY) == bool(input & NegativeY)) {
			if (input & PositiveX) {
				temp.x = 1;
			}
			else {
				temp.x = -1;
			}
		}
		else {
			input ^= pKeyboardImpl->m_LJoystickOldState;
			switch (input)
			{
			case PositiveX:
				temp.x = 1;
				break;
			case NegativeX:
				temp.x = -1;
				break;
			case PositiveY:
				temp.y = 1;
				break;
			case NegativeY:
				temp.y = -1;
				break;
			default:
				break;
			}
			input = input | IsConflict;
		}
	}
	else {
		if (bool(input & PositiveY) != bool(input & NegativeY)) {
			if (input & PositiveY) {
				temp.y = 1;
			}
			else {
				temp.y = -1;
			}
		}
	}

	if (!bool(input & IsConflict)) {
		pKeyboardImpl->m_RJoystickOldState = input;
	}
	return temp;
	//const Uint8* state = SDL_GetKeyboardState(NULL);
	//unsigned int input{};
	//for (int i = 0; i < 4; ++i) {
	//	if (state[pKeyboardImpl->m_RJoystickKeys[i]]) {
	//		input = input | 2 ^ i;
	//	}
	//}

	//glm::vec2 temp;
	//if ((input & NegativeX) != (input & PositiveX)) {
	//	if ((input & PositiveY) == (input & NegativeY)) {
	//		if (input & PositiveX) {
	//			temp.x = 1;
	//		}
	//		else {
	//			temp.x = -1;
	//		}
	//	}
	//	else {
	//		input ^= pKeyboardImpl->m_RJoystickOldState;
	//	}
	//}
	//else {
	//	if ((input & PositiveY) != (input & NegativeY)) {
	//		if (input & PositiveY) {
	//			temp.y = 1;
	//		}
	//		else {
	//			temp.y = -1;
	//		}
	//	}
	//}

	//pKeyboardImpl->m_RJoystickOldState = input;
	//return temp;
}


void dae::KeyboardInput::CheckPressedCommand()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (auto& it : pKeyboardImpl->m_PressedCommands) {
		if (state[it.first]) { //is the button currently pressed?
			if (!it.second.first) { //was the button not pressed before?
				it.second.second->Execute();
			}
			it.second.first = true;
		}
		else {
			it.second.first = false;
		}
	}
}

void dae::KeyboardInput::CheckDownCommand()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (auto& it : pKeyboardImpl->m_DownCommands) {
		if (state[it.first]) {
			it.second->Execute();
		}
	}
}

void dae::KeyboardInput::CheckReleasedCommand()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (auto& it : pKeyboardImpl->m_ReleasedCommands) {
		if (!state[it.first]) { //is the button currently not pressed?
			if (it.second.first) { //was the button pressed before?
				it.second.second->Execute();
			}
			it.second.first = false;
		}
		else {
			it.second.first = true;
		}
	}
}

void dae::KeyboardInput::CheckUpCommand()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (auto& it : pKeyboardImpl->m_UpCommands) {
		if (!state[it.first]) {
			it.second->Execute();
		}
	}
}

#pragma warning(pop)
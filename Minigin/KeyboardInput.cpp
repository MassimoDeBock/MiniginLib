#include "MiniginPCH.h"
#include "KeyboardInput.h"
#include <unordered_map>
#include "InputManager.h"

struct dae::KeyboardInput::Keyboard_Impl
{
	dae::KeyboardInput::Keyboard_Impl()
	{
	}
	SDL_Scancode m_LJoystickKeys[4]{ SDL_SCANCODE_W,	SDL_SCANCODE_A,		SDL_SCANCODE_S,		SDL_SCANCODE_D };
	glm::vec2 m_LJoystickOldState{ 0,0 };
	SDL_Scancode m_RJoystickKeys[4]{ SDL_SCANCODE_UP,	SDL_SCANCODE_LEFT,	SDL_SCANCODE_DOWN,	SDL_SCANCODE_RIGHT };
	glm::vec2 m_RJoystickOldState{ 0,0 };

	std::unordered_map<SDL_Scancode, Command*> m_PressedCommands;
	std::unordered_map<SDL_Scancode, Command*> m_DownCommands;
	std::unordered_map<SDL_Scancode, Command*> m_ReleasedCommands;
	std::unordered_map<SDL_Scancode, Command*> m_UpCommands;
	int m_ControllerIndex = -1;
};


dae::KeyboardInput::KeyboardInput()
{
	pKeyboardImpl = std::make_unique<Keyboard_Impl>(Keyboard_Impl());
}

int dae::KeyboardInput::GetControllerID() const
{
	return pKeyboardImpl->m_ControllerIndex;
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
	return glm::vec2();
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
	return glm::vec2();
}

glm::vec2 dae::KeyboardInput::GetControllerSingularNormalizeLeftThumbDirections() const
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	glm::vec2 temp;
	if (state[pKeyboardImpl->m_LJoystickKeys[3]] != state[pKeyboardImpl->m_LJoystickKeys[1]]) {
		if (!state[pKeyboardImpl->m_LJoystickKeys[0]] && !state[pKeyboardImpl->m_LJoystickKeys[2]]) {
			if (state[pKeyboardImpl->m_LJoystickKeys[3]]) {
				temp.x = 1;
			}
			else {
				temp.x = -1;
			}
		}
		else {
			temp = pKeyboardImpl->m_LJoystickOldState;
		}
	}
	else {
		if (state[pKeyboardImpl->m_LJoystickKeys[0]] != state[pKeyboardImpl->m_LJoystickKeys[2]]) {
			if (state[pKeyboardImpl->m_LJoystickKeys[0]]) {
				temp.y = 1;
			}
			else {
				temp.y = -1;
			}
		}
	}
	pKeyboardImpl->m_LJoystickOldState = temp;
	return temp;
}

glm::vec2 dae::KeyboardInput::GetControllerSingularNormalizeRightThumbDirections() const
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	glm::vec2 temp;
	if (state[pKeyboardImpl->m_RJoystickKeys[3]] != state[pKeyboardImpl->m_RJoystickKeys[1]]) {
		if (!state[pKeyboardImpl->m_RJoystickKeys[0]] && !state[pKeyboardImpl->m_RJoystickKeys[2]]) {
			if (state[pKeyboardImpl->m_RJoystickKeys[3]]) {
				temp.x = 1;
			}
			else {
				temp.x = -1;
			}
		}
		else {
			temp = pKeyboardImpl->m_RJoystickOldState;
		}
	}
	else {
		if (state[pKeyboardImpl->m_RJoystickKeys[0]] != state[pKeyboardImpl->m_RJoystickKeys[2]]) {
			if (state[pKeyboardImpl->m_RJoystickKeys[0]]) {
				temp.y = 1;
			}
			else {
				temp.y = -1;
			}
		}
	}
	pKeyboardImpl->m_RJoystickOldState = temp;
	return temp;
}


void dae::KeyboardInput::CheckPressedCommand()
{

}

void dae::KeyboardInput::CheckDownCommand()
{
	//const Uint8* state = SDL_GetKeyboardState(NULL);
	//SDL_Event event{};
	//while (SDL_PollEvent(&event)) {
	//	for (auto& it : pKeyboardImpl->m_DownCommands) {
	//		if (it.first == event.key.keysym.sym) {

	//			it.second->Execute();
	//		}
	//	}
	//}
}

void dae::KeyboardInput::CheckReleasedCommand()
{
}

void dae::KeyboardInput::CheckUpCommand()
{
}

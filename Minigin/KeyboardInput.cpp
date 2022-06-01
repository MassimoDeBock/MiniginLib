#include "MiniginPCH.h"
#include "KeyboardInput.h"
#include <unordered_map>

struct dae::KeyboardInput::Keyboard_Impl
{
	dae::KeyboardInput::Keyboard_Impl()
	{
	}
	SDL_Keycode m_LJoystickKeys[4]{ SDLK_w,		SDLK_a,		SDLK_s,		SDLK_d };
	SDL_Keycode m_RJoystickKeys[4]{ SDLK_UP,	SDLK_LEFT,	SDLK_DOWN,	SDLK_RIGHT };

	std::unordered_map<SDL_Keycode, Command*> m_PressedCommands;
	std::unordered_map<SDL_Keycode, Command*> m_DownCommands;
	std::unordered_map<SDL_Keycode, Command*> m_ReleasedCommands;
	std::unordered_map<SDL_Keycode, Command*> m_UpCommands;
	;
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

void dae::KeyboardInput::setFakeLJoystick(SDL_Keycode positiveY, SDL_Keycode negativeX, SDL_Keycode negativeY, SDL_Keycode positiveX)
{
	pKeyboardImpl->m_LJoystickKeys[0] = positiveY;
	pKeyboardImpl->m_LJoystickKeys[1] = negativeX;
	pKeyboardImpl->m_LJoystickKeys[2] = negativeY;
	pKeyboardImpl->m_LJoystickKeys[3] = positiveX;
}

void dae::KeyboardInput::setFakeRJoystick(SDL_Keycode positiveY, SDL_Keycode negativeX, SDL_Keycode negativeY, SDL_Keycode positiveX)
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

glm::vec2 dae::KeyboardInput::GetControllerNormalizedRightThumbDirections() const
{
	return glm::vec2();
}

glm::vec2 dae::KeyboardInput::GetControllerSingularNormalizeLeftThumbDirections() const
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

glm::vec2 dae::KeyboardInput::GetControllerSingularNormalizeRightThumbDirections() const
{
	return glm::vec2();
}





void dae::KeyboardInput::CheckPressedCommand()
{

}

void dae::KeyboardInput::CheckDownCommand()
{
	SDL_Event event{};
	while (SDL_PollEvent(&event)) {
		for (auto& it : pKeyboardImpl->m_DownCommands) {
			if (it.first == event.key.keysym.sym) {

				it.second->Execute();
			}
		}
	}
}

void dae::KeyboardInput::CheckReleasedCommand()
{
}

void dae::KeyboardInput::CheckUpCommand()
{
}

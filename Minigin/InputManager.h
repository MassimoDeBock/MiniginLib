#pragma once
#include "ControllerButtons.h"
#include "Singleton.h"
#include "Command.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		void Initialize();

		bool AddControllerInput(unsigned int userID, unsigned int inputID);
		bool AddKeyboardInput(unsigned int userID);

		void AddCommandsToController(unsigned int UserNumber, ControllerButton buttonID, ButtonStates state, Command* command);
		void SwapCommandsToController(unsigned int UserNumber, ControllerButton buttonID, ButtonStates state, Command* command);
		void RemoveCommandsFromController(unsigned int UserNumber, ControllerButton buttonID, ButtonStates state);
		
		void AddCommandsToKeyboard(unsigned int UserNumber, SDL_Scancode buttonCode, ButtonStates state, Command* command);
		void SwapCommandsToKeyboard(unsigned int UserNumber, SDL_Scancode buttonCode, ButtonStates state, Command* command);
		void RemoveCommandsFromKeyboard(unsigned int UserNumber, SDL_Scancode buttonCode, ButtonStates state);




		bool ProcessInput();
		bool HandleInput();
		void CheckConnections();
		glm::vec2 GetControllerLeftThumbDirections(unsigned int UserNumber) const;
		glm::vec2 GetControllerRightThumbDirections(unsigned int UserNumber) const;
		glm::vec2 GetControllerNormalizedLeftThumbDirections(unsigned int UserNumber) const;
		glm::vec2 GetControllerNormalizedRightThumbDirections(unsigned int UserNumber) const;
		glm::vec2 GetControllerSingularNormalizeLeftThumbDirections(unsigned int UserNumber) const;	//	only has -1, 0 or 1 in 1 direction
		glm::vec2 GetControllerSingularNormalizeRightThumbDirections(unsigned int UserNumber) const;	//	only has -1, 0 or 1 in 1 direction
		bool IsControllerNumberConnected(unsigned int UserNumber) const;
		
		static const unsigned int m_MaxUserCount{ 4 };

	private:


		struct Impl;
		std::unique_ptr<Impl> pimpl;
	};
}

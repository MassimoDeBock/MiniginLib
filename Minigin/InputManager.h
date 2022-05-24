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
		void AddCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state, Command* command);
		void SwapCommandsToController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state, Command* command);
		void RemoveCommandsFromController(unsigned int controllerNumber, ControllerButton buttonID, ButtonStates state);

		bool ProcessInput();
		bool HandleInput();
		void CheckConnections();
		glm::vec2 GetControllerLeftThumbDirections(unsigned int controllerNumber) const;
		glm::vec2 GetControllerRightThumbDirections(unsigned int controllerNumber) const;
		glm::vec2 GetControllerNormalizedLeftThumbDirections(unsigned int controllerNumber) const;
		glm::vec2 GetControllerNormalizedRightThumbDirections(unsigned int controllerNumber) const;
		glm::vec2 GetControllerSingularNormalizeLeftThumbDirections(unsigned int controllerNumber) const;	//	only has -1, 0 or 1 in 1 direction
		glm::vec2 GetControllerSingularNormalizeRightThumbDirections(unsigned int controllerNumber) const;	//	only has -1, 0 or 1 in 1 direction
		bool IsControllerNumberConnected(unsigned int controllerNumber) const;

	private:


		struct Impl;
		std::unique_ptr<Impl> pimpl;
	};
}

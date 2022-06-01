#pragma once
#include "Command.h"
#include "Input_API.h"

namespace dae {
	class KeyboardInput :
		public Input_API
	{
	public:
		KeyboardInput();

		virtual int GetControllerID() const;
		virtual void ProcessInput() {};
		virtual void HandleInput() {};
		virtual void CheckConnection() {};
		virtual bool IsConnected()const { return true; };

		/// <summary> Tip: the order of keys is like wasd or: (up,left,down,right) </summary>
		void setFakeLJoystick(SDL_Scancode positiveY, SDL_Scancode negativeX, SDL_Scancode negativeY, SDL_Scancode positiveX);
		/// <summary> Tip: the order of keys is like wasd or: (up,left,down,right) </summary>
		void setFakeRJoystick(SDL_Scancode positiveY, SDL_Scancode negativeX, SDL_Scancode negativeY, SDL_Scancode positiveX);

		virtual glm::vec2 GetControllerLeftThumbDirections() const;
		virtual glm::vec2 GetControllerRightThumbDirections() const;
		virtual glm::vec2 GetControllerNormalizedLeftThumbDirections() const;			//	only has -1, 0 or 1
		virtual glm::vec2 GetControllerNormalizedRightThumbDirections() const;			//	only has -1, 0 or 1
		virtual glm::vec2 GetControllerSingularNormalizeLeftThumbDirections() const;	//	only has -1, 0 or 1 in 1 direction
		virtual glm::vec2 GetControllerSingularNormalizeRightThumbDirections() const;	//	only has -1, 0 or 1 in 1 direction

	private:

		void CheckPressedCommand();
		void CheckDownCommand();
		void CheckReleasedCommand();
		void CheckUpCommand();

		struct Keyboard_Impl;
		std::unique_ptr<Keyboard_Impl> pKeyboardImpl;
	};
}
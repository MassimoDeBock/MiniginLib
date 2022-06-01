#pragma once

namespace dae {
	class Input_API
	{
	public:
		virtual ~Input_API() = default;

		virtual int GetControllerID() const = 0;
		virtual void ProcessInput() = 0;													// update input
		virtual void HandleInput() = 0;														// execute commands
		virtual void CheckConnection() = 0;
		virtual bool IsConnected()const = 0;

		virtual glm::vec2 GetControllerLeftThumbDirections() const = 0;
		virtual glm::vec2 GetControllerRightThumbDirections() const = 0;
		virtual glm::vec2 GetControllerNormalizedLeftThumbDirections() const = 0;			//	only has -1, 0 or 1
		virtual glm::vec2 GetControllerNormalizedRightThumbDirections() const = 0;			//	only has -1, 0 or 1
		virtual glm::vec2 GetControllerSingularNormalizeLeftThumbDirections() const = 0;	//	only has -1, 0 or 1 in 1 direction
		virtual glm::vec2 GetControllerSingularNormalizeRightThumbDirections() const = 0;	//	only has -1, 0 or 1 in 1 direction
	};

}
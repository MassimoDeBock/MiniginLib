#pragma once
#include "Input_API.h"
#include "Command.h"
#include "ControllerButtons.h"

namespace dae {
    class ControllerInput :
        public Input_API
    {
    public:
        ControllerInput(int controllerIndex);

        void AddCommandsToController(ControllerButton buttonID, ButtonStates state, Command* command);
        void OverrideCommands(ControllerButton buttonID, ButtonStates state, Command* command);
        void RemoveCommandsFromController(ControllerButton buttonID, ButtonStates state);
        virtual void ProcessInput();
        virtual void HandleInput();
        virtual void CheckConnection();
        virtual bool IsConnected()const;

        virtual int GetControllerID() const;

        virtual glm::vec2 GetControllerLeftThumbDirections() const;
        virtual glm::vec2 GetControllerRightThumbDirections() const;
        virtual glm::vec2 GetControllerNormalizedLeftThumbDirections() const;			//	only has -1, 0 or 1
        virtual glm::vec2 GetControllerNormalizedRightThumbDirections() const;			//	only has -1, 0 or 1
        virtual glm::vec2 GetControllerSingularNormalizeLeftThumbDirections() const;	//	only has -1, 0 or 1 in 1 direction
        virtual glm::vec2 GetControllerSingularNormalizeRightThumbDirections() const;	//	only has -1, 0 or 1 in 1 direction
    private:

        struct Controller_Impl;
        std::unique_ptr<Controller_Impl> pCtrlImpl;
    };
}
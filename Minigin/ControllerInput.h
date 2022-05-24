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
        void SwapCommandsToController(ControllerButton buttonID, ButtonStates state, Command* command);
        void RemoveCommandsFromController(ControllerButton buttonID, ButtonStates state);
    private:
        int m_ControllerIndex;

        struct Controller_Impl;
        std::unique_ptr<Controller_Impl> pCtrlImpl;
    };
}
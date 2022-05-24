#pragma once
#include "Component.h"

namespace dae {
    class InputManager;
    class BasePlayerController :
        public Component
    {
    public:
        BasePlayerController(const int playerID);
        virtual ~BasePlayerController();

        int GetPlayerID();
    protected:
        InputManager& m_Inputmanager;
    private:
        const int m_PlayerID;

    };
    
}
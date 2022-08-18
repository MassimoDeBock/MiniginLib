#pragma once

#include <Component.h>

class PlayerTankComponent final :
    public dae::Component
{
public:
    PlayerTankComponent(const int playerID);
    ~PlayerTankComponent()override;

    void Update() override;
    void Render()const override;
    void OnAssign() override;
    void BeginPlay() override;

};


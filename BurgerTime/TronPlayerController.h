#pragma once
#include "BasePlayerController.h"

class TankMovementComponent;
class TronPlayerController :
	public dae::BasePlayerController
{
public:
	TronPlayerController(const int playerID, TankMovementComponent* movementComponent );
	virtual ~TronPlayerController();
	void Update() override;
	void OnAssign() override;
private:
	TankMovementComponent* m_MovementComponent{ nullptr };
};


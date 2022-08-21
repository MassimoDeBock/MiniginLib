#pragma once
#include "BasePlayerController.h"

class TankMovementComponent;
class TankComponent;
class TronPlayerController :
	public dae::BasePlayerController
{
public:
	TronPlayerController(const int playerID, TankComponent* tankComponent,TankMovementComponent* movementComponent );
	virtual ~TronPlayerController();
	void Update() override;
	void OnAssign() override;
private:
	TankMovementComponent* m_MovementComponent{ nullptr };
	TankComponent* m_TankComponent{ nullptr };
};


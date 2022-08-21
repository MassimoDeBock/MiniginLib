#pragma once
#include "BasePlayerController.h"

namespace dae {
	class MovementComponent;
	class PeterPepperPlayerController final : public BasePlayerController
	{
	public:
		PeterPepperPlayerController(const int playerID);
		virtual ~PeterPepperPlayerController();
		void Update() override;
		void OnAssign() override;

	private:
		MovementComponent* m_MovementComponent{nullptr};
	};
}
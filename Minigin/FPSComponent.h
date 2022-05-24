#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace dae {
	class FPSComponent : public Component
	{
	public:

		FPSComponent();
		void Update() override;
		void Render() const override;
		void SetParent(GameObject* parentGameObject) override;

	private:
		std::unique_ptr<TextComponent> m_textComponent;
		int m_UpdateEveryXFrames{ 80 }; //60=1sec 30=0.5sec
		int m_UpdateFrameCounter{ m_UpdateEveryXFrames - 2 };

	};

}
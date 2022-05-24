#pragma once
#include "Component.h"

namespace dae {
	class Texture2D;
	class TextureComponent : public Component
	{
	public:
		std::shared_ptr<Texture2D> m_Texture{};
		TextureComponent(const std::string& filename);

		void SetTexture(const std::string& filename);
		void Update() override;
		void Render() const override;
	};
}
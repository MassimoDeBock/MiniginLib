#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae {
	class Texture2D;
	class Transform;
	class TextureComponent : public Component
	{
	public:
		std::shared_ptr<Texture2D> m_Texture{};
		TextureComponent(const std::string& filename);
		TextureComponent(const std::string& filename, Transform offset);

		void SetTexture(const std::string& filename);
		void Update() override;
		void Render() const override;
	private:
		Transform m_Offset{0,0};
	};
}
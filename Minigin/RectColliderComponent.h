#pragma once
#include "Component.h"
#include "Subject.h"
#define COLLIDER_MARGIN 0.05f

namespace dae {
	class RectColliderComponent :
		public Component
	{
	public:
		RectColliderComponent(const glm::vec2& size, const glm::vec2& offset = glm::vec2(0,0));
		virtual void OnAssign() override;
		virtual void Render()const override;
		virtual void FixedUpdate() override;
		virtual void BeginPlay() override;

		bool IsOverlapping(const RectColliderComponent* right);

		void Hits(const RectColliderComponent* other);
		void IsHit(const RectColliderComponent* other);

		void DoVisualise(bool newIsVisualize);
		void SetVisualizeColor(const SDL_Color& color);

		void TestCollisions();
 		Subject m_Subject;
	private:
		bool m_IsVisualize{false};
		SDL_Color m_VisualizeColor{0,0,0};

		glm::vec2 m_LastPos;
		glm::vec2 m_Offset;
		glm::vec2 m_Size;


		bool m_multiHit = true;
	};

}
#include "MiniginPCH.h"
#include "RectColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Renderer.h"

dae::RectColliderComponent::RectColliderComponent(const glm::vec2& size, const glm::vec2& offset)
	: m_Offset(offset),
	m_Size(size)
{
}

void dae::RectColliderComponent::OnAssign()
{
	if (m_GameObjectRef->m_sceneRef != nullptr) {
			m_GameObjectRef->m_sceneRef->m_CollisionManager.AddRectCollider(this);
	}
	else {
		std::cout << "Make sure the RectColliderComponent Is added to a gameObject that's in a scene firt\n";
	}
}

void dae::RectColliderComponent::Render() const
{
	if (m_IsVisualize == false) return;
	auto pos = m_GameObjectRef->GetAbsoluteTransform().GetPosition();
	const SDL_Rect rect = SDL_Rect(int(pos.x + m_Offset.x), int(pos.y + m_Offset.y), int(m_Size.x),int( m_Size.y));

	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), m_VisualizeColor.r, m_VisualizeColor.g, m_VisualizeColor.b, m_VisualizeColor.a);
	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
}

void dae::RectColliderComponent::FixedUpdate()
{
	glm::vec2 pos = m_GameObjectRef->GetAbsoluteTransform().GetPosition();
	if (abs(pos.x - m_LastPos.x)< COLLIDER_MARGIN && abs(pos.y - m_LastPos.y)< COLLIDER_MARGIN) return;
	m_LastPos = glm::vec2(pos.x, pos.y);
	this->TestCollisions();
}

void dae::RectColliderComponent::BeginPlay()
{
}

bool dae::RectColliderComponent::IsOverlapping(const RectColliderComponent* right)
{
	if (this == right)return false;
	glm::vec3 pThisLocation = this->m_GameObjectRef->GetAbsoluteTransform().GetPosition();
	glm::vec3 pRightLocation = right->m_GameObjectRef->GetAbsoluteTransform().GetPosition();

	glm::vec2 thisLT{	pThisLocation.x + this->m_Offset.x,
						pThisLocation.y + this->m_Offset.y
	};
	glm::vec2 thisRB{	thisLT.x + this->m_Size.x,
						thisLT.y + this->m_Size.y
	};
	glm::vec2 otherLT{	pRightLocation.x + right->m_Offset.x,
						pRightLocation.y + right->m_Offset.y
	};
	glm::vec2 otherRB{	otherLT.x +	right->m_Size.x,
						otherLT.y + right->m_Size.y
	};

	if (thisLT.y	>	otherRB.y	||
		thisRB.y	<	otherLT.y	||
		thisLT.x	>	otherRB.x	||
		thisRB.x	<	otherLT.x	) {
		return false;
	}
	return true;
}

void dae::RectColliderComponent::Hits(const RectColliderComponent* other)
{
	m_Subject.Notify(*other->m_GameObjectRef, Event::Hits);
}

void dae::RectColliderComponent::IsHit(const RectColliderComponent* other)
{
	m_Subject.Notify(*other->m_GameObjectRef, Event::IsHit);
}

void dae::RectColliderComponent::DoVisualise(bool newIsVisualize)
{
	m_IsVisualize = newIsVisualize;
}

void dae::RectColliderComponent::SetVisualizeColor(const SDL_Color& color)
{
	m_VisualizeColor = color;
}


void dae::RectColliderComponent::TestCollisions()
{

	m_GameObjectRef->m_sceneRef->m_CollisionManager.CheckCollisions(this);
}

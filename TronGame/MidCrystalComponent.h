#pragma once
#include <Component.h>
#include <Observer.h>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

namespace dae{
	class Subject;
}

class MidCrystalComponent :
	public dae::Component, public dae::Observer
{
public:
	MidCrystalComponent(const int x, const int y);
	virtual ~MidCrystalComponent();

	void OnAssign() override;

	virtual void OnNotify(const dae::GameObject& gameObject, dae::Event eventType, int optionalValue = 0) override;
	virtual void OnNotifyHitbox(const dae::GameObject& gameObject, dae::RectColliderComponent* other, dae::Event eventType, int optionalValue = 0) override;
	virtual void OnNotifyNoReturn(dae::Event eventType, int optionalValue = 0);

private:
	void HandleEvents(const dae::GameObject& gameObject, dae::RectColliderComponent* other, dae::Event eventType, int optionalValue);
	void IsHit(const dae::GameObject& gameObject);

	const glm::vec2 m_Size;
};
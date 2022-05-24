#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform::Transform()
{
}

dae::Transform::Transform(float x, float y, float z)
{
	SetPosition(x, y, z);
}

dae::Transform::Transform(glm::vec3 vec3)
	:m_Position(vec3)
{
}

dae::Transform::Transform(const Transform& transform)
	: m_Position(transform.GetPosition())
{
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::SetPosition(const Transform& transform)
{
	m_Position = transform.GetPosition();
}

dae::Transform dae::Transform::operator+(const Transform& right)
{
	return Transform(
		this->GetPosition().x + right.GetPosition().x,
		this->GetPosition().y + right.GetPosition().y,
		this->GetPosition().z + right.GetPosition().z
	);
}

dae::Transform& dae::Transform::operator+=(const Transform& right)
{
	this->m_Position.x += right.GetPosition().x;
	this->m_Position.y += right.GetPosition().y;
	this->m_Position.z += right.GetPosition().z;
	return *this;
}

dae::Transform dae::Transform::operator*(const Transform& right)
{
	return Transform(
		this->GetPosition().x * right.GetPosition().x,
		this->GetPosition().y * right.GetPosition().y,
		this->GetPosition().z * right.GetPosition().z	
	);
}

dae::Transform& dae::Transform::operator*=(const Transform& right)
{
	this->m_Position.x -= right.GetPosition().x;
	this->m_Position.y -= right.GetPosition().y;
	this->m_Position.z -= right.GetPosition().z;
	return *this;
}

dae::Transform dae::Transform::operator*(const float& right)
{
	return Transform(
		this->GetPosition().x * right,
		this->GetPosition().y * right,
		this->GetPosition().z * right
	);
}

dae::Transform& dae::Transform::operator*=(const float& right)
{
	this->m_Position.x *= right;
	this->m_Position.y *= right;
	this->m_Position.z *= right;
	return *this;
}

dae::Transform dae::Transform::operator+(const glm::vec2& right)
{
	return Transform(
		this->GetPosition().x + right.x,
		this->GetPosition().y + right.y,
		this->GetPosition().z
	);
}

dae::Transform dae::Transform::operator-(const glm::vec2& right)
{
	return Transform(
		this->GetPosition().x - right.x,
		this->GetPosition().y - right.y,
		this->GetPosition().z
	);
}


dae::Transform dae::Transform::operator-(const Transform& right)
{
	return Transform(
		this->GetPosition().x - right.GetPosition().x,
		this->GetPosition().y - right.GetPosition().y,
		this->GetPosition().z - right.GetPosition().z
	);
}

dae::Transform& dae::Transform::operator-=(const Transform& right)
{
	this->m_Position.x -= right.GetPosition().x;
	this->m_Position.y -= right.GetPosition().y;
	this->m_Position.z -= right.GetPosition().z;
	return *this;
}

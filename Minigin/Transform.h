#pragma once
namespace dae
{
	class Transform final
	{
	public:
		Transform();
		Transform(float x, float y, float z =0);
		Transform(glm::vec3 vec3);
		Transform(const Transform& transform);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(const Transform& transform);
		Transform operator+(const Transform& right);
		Transform& operator+=(const Transform& right);
		Transform operator-(const Transform& right);
		Transform& operator-=(const Transform& right);
		Transform operator*(const Transform& right);
		Transform& operator*=(const Transform& right);
		Transform operator*(const float& right);
		Transform& operator*=(const float& right);

		Transform operator+(const glm::vec2& right);
		Transform operator-(const glm::vec2& right);


	private:
		glm::vec3 m_Position;
	};
}

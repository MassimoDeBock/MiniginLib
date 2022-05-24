#pragma once

namespace dae {
	class GameObject;
	class Component
	{
		//functions
	public:
		Component();
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
		virtual void SetParent(GameObject* parentGameObject);

	private:


		//variables
	public:
		virtual void OnAssign() {}; //regular constructor doesn't have the owning object yet / this happens after the component is assigned one
		virtual void Update() {};
		virtual void FixedUpdate() {};
		virtual void BeginPlay() {};
		virtual void Render()const {};

	protected:
		GameObject* m_GameObjectRef = nullptr;

	};
}


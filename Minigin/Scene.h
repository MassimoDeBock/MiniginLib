#pragma once
#include "SceneManager.h"
#include "Component.h"
#include "CollisionManager.h"
#include <map>
#include <list>

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::string& objectName, const std::shared_ptr<GameObject>& object);
		GameObject* GetGameObject(const std::string& objectName);

		void Update(float deltaTime);
		void FixedUpdate();
		void BeginPlay();
		void Render() const;
		float GetDeltaTime();
		float GetFixedTimeStep();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		CollisionManager m_CollisionManager;

	private:
		explicit Scene(const std::string& name, float fixedTimeStep);

		
		float m_deltaTime;
		const float m_FixedTimeStep;
		std::string m_Name;

		std::map <std::string ,std::shared_ptr<GameObject>> m_GameObjects;
	};

}

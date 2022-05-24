#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate();
		void BeginPlay();
		void Render();
		void SetFixedTimeStep(float newFixedTimeStep);
		float GetFixedTimeStep();

	private:
		float m_FixedTimeStep{10.0f};
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}

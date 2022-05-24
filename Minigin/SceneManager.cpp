#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for (auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate();
	}
}

void dae::SceneManager::BeginPlay()
{
	for (auto& scene : m_Scenes)
	{
		scene->BeginPlay();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::SetFixedTimeStep(float newFixedTimeStep)
{
	m_FixedTimeStep = newFixedTimeStep;
}

float dae::SceneManager::GetFixedTimeStep()
{
	return m_FixedTimeStep;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name,m_FixedTimeStep));
	m_Scenes.push_back(scene);
	return *scene;
}

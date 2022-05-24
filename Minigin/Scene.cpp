#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

Scene::Scene(const std::string& name, float fixedTimeStep) : m_Name(name), m_deltaTime(0.0f), m_FixedTimeStep(fixedTimeStep), m_CollisionManager()
{}

Scene::~Scene() {
};

void Scene::Add(const std::string & objectName, const std::shared_ptr<GameObject>&object)
{
	object.get()->setSceneRef(*this);
	m_GameObjects.insert(std::pair<std::string, std::shared_ptr<GameObject>>(objectName, object));
}

GameObject* dae::Scene::GetGameObject(const std::string & objectName)
{
	auto object = m_GameObjects.find(objectName);
	if (object != m_GameObjects.end()) {
		return object->second.get();
	}
	return nullptr;
}

void Scene::Update(float deltaTime)
{
	m_deltaTime = deltaTime;
	for (auto& object : m_GameObjects)
	{
		object.second->Update();
	}
}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_GameObjects)
	{
		object.second->FixedUpdate();
	}
}

void dae::Scene::BeginPlay()
{
	for (auto& object : m_GameObjects)
	{
		object.second->BeginPlay();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_GameObjects)
	{
		object.second->Render();
	}
}

float dae::Scene::GetDeltaTime()
{
	return m_deltaTime;
}

float dae::Scene::GetFixedTimeStep()
{
	return m_FixedTimeStep;
}
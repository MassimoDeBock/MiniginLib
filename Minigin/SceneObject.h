#pragma once
namespace dae
{
	class Scene;
	class SceneObject
	{
	public:
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void BeginPlay() = 0;
		virtual void Render() const = 0;
		void setSceneRef(Scene& ref) { m_sceneRef = &ref; };

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
		Scene* m_sceneRef{ nullptr };
	};
}

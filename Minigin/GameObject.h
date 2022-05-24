#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "Tags.h"

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void FixedUpdate() override;
		void BeginPlay() override;
		void Render() const override;

		void SetRelativeTransform(float x, float y);
		void SetRelativeTransform(const Transform& pos);
		void SetAbsoluteTransform(float x, float y);
		void SetAbsoluteTransform(const Transform& pos);
		void UpdateAbsoluteTransform() const;
		void AddTransform(const Transform& translation);

		void SetTag(Tag tag);
		Tag GetTag() const;

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		std::unordered_map<std::string, Component*> m_Components;
		Transform GetRelativeTransform() const;
		Transform GetAbsoluteTransform() const;
		void SetTransformDirty();

		void SetParent(GameObject* newParent, bool AbsoluteTransformStays = false);


	private:
		void RemoveChild(GameObject* oldChild);
		void AddChild(GameObject* newChild);
	public:
		template <typename T> T* GetComponent(const std::string& componentName) const {
			std::unordered_map<std::string, Component*>::const_iterator compIt = m_Components.find(componentName);
			if (compIt != m_Components.end()) {
				return dynamic_cast<T*>(compIt->second);
			}
			return nullptr;
		}

		template <typename T> void AddComponent(const std::string& componentName, T* component) {
			if (Component* comp = dynamic_cast<Component*>(component); comp != nullptr) {
				comp->SetParent(this);
				m_Components.insert(std::pair<std::string, Component*>(componentName, comp));
				comp->OnAssign();
			}
		};

	private:
		
		Tag m_Tag{Tag::none};

		mutable bool m_TransformIsDirty{ true };
		GameObject* m_pParent{ nullptr };
		std::unordered_set<GameObject*> m_Children;

		Transform m_RelativeTransform{};
		mutable Transform m_AbsoluteTransform{};
	public:
	};

}


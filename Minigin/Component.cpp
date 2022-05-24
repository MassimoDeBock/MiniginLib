#include "MiniginPCH.h"
#include "Component.h"


dae::Component::Component() 
{
}

void dae::Component::SetParent(GameObject* parentGameObjectRef) {
	m_GameObjectRef = parentGameObjectRef;
}
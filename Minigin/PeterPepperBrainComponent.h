#pragma once
#include "Component.h"
#include "Observer.h"
#include "Subject.h"


namespace dae {
    class SpriteGroup;
    class PeterPepperBrainComponent final:
        public Component, public Observer
    {
    public:
        PeterPepperBrainComponent(const int playerID);
        virtual ~PeterPepperBrainComponent();

        void Update() override;
        void Render()const override;
        void OnAssign() override;
        void BeginPlay() override;

        void GetPoints(const int value);

        void OnNotify(const GameObject& gameObject, Event eventType, int optionalValue = 0) override;

        Subject m_Subject{};
    private: 
        void HandleEvents(const GameObject& gameObject, Event eventType, int optionalValue = 0);
        void Hits(const GameObject& gameObject);
        void Dies();

        const int m_PlayerID;
        glm::vec2 m_SpawnLocation;

        std::shared_ptr<dae::SpriteGroup> m_SpriteGroup;
    };
}
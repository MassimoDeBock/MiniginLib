#pragma once
#include "Component.h"
#include "Observer.h"
#include "Subject.h"


namespace dae {
    class SpriteGroup;
    class MovementComponent;
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
        enum class SpritesOrder {
            Up          = 0,
            Left        = 10,
            Right       = 20,
            Down        = 30,
            Shooting    = 40,
            Dying       = 50
        };

        void CalcDirection();
        void LoadSprites();
        void HandleEvents(const GameObject& gameObject, Event eventType, int optionalValue = 0);
        void Hits(const GameObject& gameObject);
        void Dies();

        bool m_isMoving{ false };
        int m_ImgCounter{ 0 };
        float m_Tick{ 0.0f };
        float m_SpriteUpdatePerSecond{ 0.2f };
        SpritesOrder m_CurrentDirection{ SpritesOrder::Left };

        const int m_PlayerID;
        glm::vec2 m_SpawnLocation;

        std::shared_ptr<dae::MovementComponent> m_MovementComponent;
        std::shared_ptr<dae::SpriteGroup> m_SpriteGroup;
    };
}
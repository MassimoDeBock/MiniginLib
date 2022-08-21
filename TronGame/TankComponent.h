#pragma once
#include <Component.h>
#include <memory>
#include <Observer.h>
#include <Subject.h>
#include <Event.h>

namespace dae {
    class SpriteGroup;
    class Texture2D;
    class Transform;
    class GameObject;
}
class BulletHandlerComponent;
class TankMovementComponent;
class TankComponent final :
    public dae::Component, public dae::Observer
{
public:
    TankComponent(const int playerID, int teamID = 0, int spriteRow = 0);
    ~TankComponent()override;

    void Update() override;
    void Render()const override;
    void OnAssign() override;
    void BeginPlay() override;

    void Shoot(dae::Transform direction);

    void OnNotify(const dae::GameObject& gameObject, dae::Event event, int optionalValue = 0);
    void OnNotifyNoReturn(dae::Event eventType, int optionalValue = 0)override;


private:
    enum class SpritesOrder {
        Up = 3,
        Left = 2,
        Right = 0,
        Down = 1
    };

    void LoadSprites();
    void HandleEvents(dae::Event eventType, int optionalValue = 0);
    void TakeDamage(int damage = 1);
    void Dies();

    std::shared_ptr<dae::Texture2D> m_BulletTexture;

    float m_MoveSpeed{ 0.4f };
    SpritesOrder m_CurrentDirection{ SpritesOrder::Up };

    int m_HP{ 3 };
    const int m_PlayerID;
    const int m_TeamID;
    TankMovementComponent* m_MovementComponent{nullptr};
    std::shared_ptr<dae::SpriteGroup> m_SpriteGroup{};
    int m_SpriteVariationRow{0};
    BulletHandlerComponent* m_BulletHandler{ nullptr };
    float m_FireRate{1};
    float m_FireRateCD{ m_FireRate };
};


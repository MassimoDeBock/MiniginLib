#pragma once
#include <Component.h>
#include <memory>


namespace dae {
    class SpriteGroup;
}
class TankMovementComponent;
class TankComponent final :
    public dae::Component
{
public:
    TankComponent(const int playerID,int spriteRow);
    ~TankComponent()override;

    void Update() override;
    void Render()const override;
    void OnAssign() override;
    void BeginPlay() override;

private:
    enum class SpritesOrder {
        Up = 3,
        Left = 2,
        Right = 0,
        Down = 1
    };

    void LoadSprites();

    float m_MoveSpeed{ 0.2f };
    SpritesOrder m_CurrentDirection{ SpritesOrder::Up };


    const int m_PlayerID;
    TankMovementComponent* m_MovementComponent{nullptr};
    std::shared_ptr<dae::SpriteGroup> m_SpriteGroup{};
    int m_SpriteVariationRow{0};
};


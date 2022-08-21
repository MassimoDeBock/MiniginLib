#pragma once
#include <Component.h>
#include "MapComponent.h"
#include <Transform.h>

//class MapComponent;
namespace dae {
    class Transform;
}
class TankMovementComponent final :
    public dae::Component
{
public:

    enum class MoveDirection {
        Up = 3,
        Left = 2,
        Right = 0,
        Down = 1
    };


    TankMovementComponent(const float movementSpeed);
    void FixedUpdate() override;
    void OnAssign() override;
    dae::Transform GetVelocity() const;

    TankMovementComponent::MoveDirection GetMoveDirection()const;

    void SetVelocity(const dae::Transform& newVelocity);

private:
    void CalcGridPos();
    void RegulateMovement();

    MoveDirection m_MoveDirection{ MoveDirection::Down };
    dae::Transform m_CellOffset{0,0};
    int m_RowY{ 0 };
    int m_ColX{ 0 };
    dae::Transform m_Velocity{0,0};
    float m_MoveSpeed{ 1.0f };
    MapComponent* m_MapRef{nullptr};
};


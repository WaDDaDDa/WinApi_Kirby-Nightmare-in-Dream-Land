#pragma once
#include "Kirby.h"

class BurningKirby : public Kirby
{
public:
    BurningKirby();
    ~BurningKirby();

    BurningKirby(const BurningKirby& _Other) = delete;
    BurningKirby(BurningKirby&& _Other) noexcept = delete;
    BurningKirby& operator=(const BurningKirby& _Other) = delete;
    BurningKirby& operator=(BurningKirby&& _Other) noexcept = delete;

    void ChangeAnimationState(const std::string& _StateName) override;

    void Start() override;
    void Update(float _Delta) override;
    void CameraFocus(float _Delta) override;
    void LevelStart() override;
protected:

    void AttackStartStart() override;
    void AttackStart() override;

    void AttackStartUpdate(float _Delta) override;
    void AttackUpdate(float _Delta) override;

    void JumpAttackStartStart() override;
    void JumpAttackStart() override;
  
    void JumpAttackStartUpdate(float _Delta) override;
    void JumpAttackUpdate(float _Delta) override;

    void DamageStart() override;

private:

    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float4 BodyCollisionPos = float4{ 0 , -40 };
    float4 BodyCollisionScale = float4{ 80, 80 };
    float4 AttackCollisionPos = float4{ 0 , -40 };
    float4 AttackCollisionScale = float4{ 130,100 };

    float Speed = 400.0f;
    float JumpPower = 800.0f;

};


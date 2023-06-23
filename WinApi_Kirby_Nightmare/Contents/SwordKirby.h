#pragma once
#include "Kirby.h"

class SwordKirby : public Kirby
{
public:
    SwordKirby();
    ~SwordKirby();

    SwordKirby(const SwordKirby& _Other) = delete;
    SwordKirby(SwordKirby&& _Other) noexcept = delete;
    SwordKirby& operator=(const SwordKirby& _Other) = delete;
    SwordKirby& operator=(SwordKirby&& _Other) noexcept = delete;

    void ChangeAnimationState(const std::string& _StateName) override;

    void Start() override;
    void Update(float _Delta) override;
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
    class GameEngineRenderer* LeftAttRenderer = nullptr;
    GameEngineRenderer* RightAttRenderer = nullptr;

    GameEngineCollision* LeftAttackCollision = nullptr;
    GameEngineCollision* RightAttackCollision = nullptr;
    GameEngineCollision* JumpAttackCollision = nullptr;

    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float4 BodyCollisionPos = float4{ 0 , -40 };
    float4 BodyCollisionScale = float4{ 80, 80 };

    float4 LeftAttackCollisionPos = float4{ -110.0f , -45 };
    float4 LeftAttackCollisionScale = float4{ 200,150 };

    float4 RightAttackCollisionPos = float4{ 110.0f , -45 };
    float4 RightAttackCollisionScale = float4{ 200,150 };

    float4 JumpAttackCollisionPos = float4{ 0.0f , -60 };
    float4 JumpAttackCollisionScale = float4{ 150,150 };

    float Speed = 400.0f;
    float JumpPower = 800.0f;

};


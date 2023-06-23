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

    void JumpAttackStartStart(float _Delta);
    void JumpAttackStartUpdate(float _Delta);

    void JumpAttackStart(float _Delta);
    void JumpAttackUpdate(float _Delta);

    void DamageStart() override;

private:
    class GameEngineRenderer* AttRenderer = nullptr;

    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float4 BodyCollisionPos = float4{ 0 , -40 };
    float4 BodyCollisionScale = float4{ 80, 80 };
    float4 AttackCollisionPos = float4{ -2.5f , -30 };
    float4 AttackCollisionScale = float4{ 150,150 };


    float Speed = 400.0f;
    float JumpPower = 800.0f;

};


#pragma once
#include "Kirby.h"


class WheelKirby : public Kirby
{
public:
    WheelKirby();
    ~WheelKirby();

    WheelKirby(const WheelKirby& _Other) = delete;
    WheelKirby(WheelKirby&& _Other) noexcept = delete;
    WheelKirby& operator=(const WheelKirby& _Other) = delete;
    WheelKirby& operator=(WheelKirby&& _Other) noexcept = delete;

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

    void DirChangeStart() override;
    void DirChangeUpdate(float _Delta) override;

private:
    GameEngineCollision* AttCollision = nullptr;

    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float4 BodyCollisionPos = float4{ 0 , -40 };
    float4 BodyCollisionScale = float4{ 80, 80 };

    float4 AttCollisionScale = float4{ 120, 120 };
    float4 AttCollisionPos = float4{ 0 , -40 };

    class GameEngineSoundPlayer SoundEffect;
    KirbyDir CurDir;
};


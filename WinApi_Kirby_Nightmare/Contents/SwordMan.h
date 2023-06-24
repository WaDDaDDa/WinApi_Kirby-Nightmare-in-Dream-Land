#pragma once
#include "Monster.h"

enum class SwordManState
{
    Idle,
    DownIdle,
    Tackle,
    Walk,
    Jump,
    JumpTurn,
    Falling,
    FallingEnd,
    Run,
    Fly,
    BreathIn,
    AttackStart,
    Attack,
    HitReady,
    Hit,
    Damage,
    Effect,
    Max, // 일반적으로 사용하지 않는 값.
};

enum class SwordManDir
{
    Right,
    Left,
};

class GameEngineRenderer;
class SwordMan : public Monster
{
public:
    SwordMan();
    ~SwordMan();

    SwordMan(const SwordMan& _Other) = delete;
    SwordMan(SwordMan&& _Other) noexcept = delete;
    SwordMan& operator=(const SwordMan& _Other) = delete;
    SwordMan& operator=(SwordMan&& _Other) noexcept = delete;

    GameEngineRenderer* MainRenderer = nullptr;

    SwordManState State = SwordManState::Max;
    void StateUpdate(float _Delta);
    void IdleStart();
    void IdleUpdate(float _Delta);
    void WalkStart();
    void WalkUpdate(float _Delta);
    void HitReadyStart();
    void HitReadyUpdate(float _Delta);
    void HitStart();
    void HitUpdate(float _Delta);
    void DamageStart();
    void DamageUpdate(float _Delta);
    void EffectStart();
    void EffectUpdate(float _Delta);
    void AttackStartStart();
    void AttackStartUpdate(float _Delta);
    void AttackStart();
    void AttackUpdate(float _Delta);

    void ChangeState(SwordManState _State);

    SwordManDir GetDir()
    {
        return Dir;
    }

    SwordManDir Dir = SwordManDir::Right;
    std::string CurState = "";

    void ChangeAnimationState(const std::string& _StateName);

protected:

    unsigned int GetWallCheck();
    void Movement(float _Delta);

private:
    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float Speed = 200.0f;
    float AttRange = 300.0f;

    void Start() override;

    void Update(float _Delta) override;

    GameEngineCollision* BodyCollision = nullptr;
    GameEngineCollision* DeathCollision = nullptr;

    GameEngineCollision* LeftAttackCollision = nullptr;
    GameEngineCollision* RightAttackCollision = nullptr;

    float4 CollisionPos = float4{ 0 , -40 };
    float4 CollisionScale = float4{ 80, 80 };
    float4 DeathCollisionScale = float4{ 100, 100 };

    float4 LeftAttackCollisionPos = float4{ -100.0f , -40 };
    float4 LeftAttackCollisionScale = float4{ 150,100 };

    float4 RightAttackCollisionPos = float4{ 100.0f , -40 };
    float4 RightAttackCollisionScale = float4{ 150,100 };

    GameEngineActor* Actor = nullptr;
    // Abillity CurAbillity = Abillity::Normal;
};


#pragma once
#include "Monster.h"

enum class WaddleDeeState
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

enum class WaddleDeeDir
{
    Right,
    Left,
};

class GameEngineRenderer;
class WaddleDee : public Monster
{
public:
    WaddleDee();
    ~WaddleDee();

    WaddleDee(const WaddleDee& _Other) = delete;
    WaddleDee(WaddleDee&& _Other) noexcept = delete;
    WaddleDee& operator=(const WaddleDee& _Other) = delete;
    WaddleDee& operator=(WaddleDee&& _Other) noexcept = delete;

    GameEngineRenderer* MainRenderer = nullptr;

    WaddleDeeState State = WaddleDeeState::Max;
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


    void ChangeState(WaddleDeeState _State);

    WaddleDeeDir Dir = WaddleDeeDir::Right;
    std::string CurState = "";

    void ChangeAnimationState(const std::string& _StateName);

protected:

    unsigned int GetWallCheck();
    void Movement(float _Delta);

private:
    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float Speed = 200.0f;

    void Start() override;

    void Update(float _Delta) override;

    GameEngineCollision* BodyCollision = nullptr;
    GameEngineCollision* DeathCollision = nullptr;
    float4 CollisionPos = float4{ 0 , -40 };
    float4 CollisionScale = float4{ 80, 80 };
    float4 DeathCollisionScale = float4{ 100, 100 };

    GameEngineActor* Actor = nullptr;
    Abillity CurAbillity = Abillity::Normal;
};


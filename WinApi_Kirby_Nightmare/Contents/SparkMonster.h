#pragma once
#include "Monster.h"

enum class SparkMonsterState
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

enum class SparkMonsterDir
{
    Right,
    Left,
};

class GameEngineRenderer;
class SparkMonster : public Monster
{
public:
    SparkMonster();
    ~SparkMonster();

    SparkMonster(const SparkMonster& _Other) = delete;
    SparkMonster(SparkMonster&& _Other) noexcept = delete;
    SparkMonster& operator=(const SparkMonster& _Other) = delete;
    SparkMonster& operator=(SparkMonster&& _Other) noexcept = delete;


    SparkMonsterState State = SparkMonsterState::Max;
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

    void ChangeState(SparkMonsterState _State);

    SparkMonsterDir GetDir()
    {
        return Dir;
    }

    SparkMonsterDir Dir = SparkMonsterDir::Right;
    std::string CurState = "";

    void ChangeAnimationState(const std::string& _StateName);

protected:

    unsigned int GetWallCheck();
    void Movement(float _Delta);

private:
    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float Speed = 400.0f;
    float JumpPower = 800.0f;
    float AttRange = 300.0f;

    void Start() override;

    void Update(float _Delta) override;

    GameEngineCollision* BodyCollision = nullptr;
    GameEngineCollision* DeathCollision = nullptr;
    GameEngineCollision* AttackCollision = nullptr;

    class GameEngineRenderer* AttRenderer = nullptr;
    GameEngineRenderer* MainRenderer = nullptr;

    float4 CollisionPos = float4{ 0 , -40 };
    float4 CollisionScale = float4{ 80, 80 };

    float4 DeathCollisionScale = float4{ 100, 100 };
    float4 AttackCollisionPos = float4{ 0 , -30 };
    float4 AttackCollisionScale = float4{ 140,140 };

    GameEngineActor* Actor = nullptr;
};


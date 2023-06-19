#pragma once
#include "Monster.h"

enum class BurningMonsterState
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
    Attack1,
    Attack2,
    HitReady,
    Hit,
    Damage,
    Effect,
    Max, // 일반적으로 사용하지 않는 값.
};

enum class BurningMonsterDir
{
    Right,
    Left,
};

class GameEngineRenderer;
class BurningMonster : public Monster
{
public:
    BurningMonster();
    ~BurningMonster();

    BurningMonster(const BurningMonster& _Other) = delete;
    BurningMonster(BurningMonster&& _Other) noexcept = delete;
    BurningMonster& operator=(const BurningMonster& _Other) = delete;
    BurningMonster& operator=(BurningMonster&& _Other) noexcept = delete;

    GameEngineRenderer* MainRenderer = nullptr;

    GameEngineRenderer* LeftAttackRenderer = nullptr;
    GameEngineRenderer* LeftAttack2Renderer = nullptr;

    GameEngineRenderer* RightAttackRenderer = nullptr;
    GameEngineRenderer* RightAttack2Renderer = nullptr;

    BurningMonsterState State = BurningMonsterState::Max;
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
    void Attack1Start();
    void Attack1Update(float _Delta);
    void Attack2Start();
    void Attack2Update(float _Delta);

    void ChangeState(BurningMonsterState _State);

    BurningMonsterDir GetDir()
    {
        return Dir;
    }

    BurningMonsterDir Dir = BurningMonsterDir::Right;
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
    GameEngineCollision* AttackCollision = nullptr;

    float4 CollisionPos = float4{ 0 , -40 };
    float4 CollisionScale = float4{ 80, 80 };
    float4 DeathCollisionScale = float4{ 100, 100 };

    float4 AttackCollisionPos = float4{ 100 , -40 };
    float4 AttackCollisionScale = float4{ 80,80 };

    GameEngineActor* Actor = nullptr;
    // Abillity CurAbillity = Abillity::Normal;
};


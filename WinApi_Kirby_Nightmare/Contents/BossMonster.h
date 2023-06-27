#pragma once
#include "Monster.h"

enum class BossMonsterState
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
    AttackStay,
    Attack,
    HitReady,
    Hit,
    Damage,
    Effect,
    Max, // 일반적으로 사용하지 않는 값.
};

enum class BossMonsterDir
{
    Right,
    Left,
};

class GameEngineRenderer;
class BossMonster : public Monster
{
public:
    BossMonster();
    ~BossMonster();

    BossMonster(const BossMonster& _Other) = delete;
    BossMonster(BossMonster&& _Other) noexcept = delete;
    BossMonster& operator=(const BossMonster& _Other) = delete;
    BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

    GameEngineRenderer* MainRenderer = nullptr;

    BossMonsterState State = BossMonsterState::Max;
    void StateUpdate(float _Delta);

    void IdleStart();
    void IdleUpdate(float _Delta);

    void DamageStart();
    void DamageUpdate(float _Delta);

    void AttackStayStart();
    void AttackStayUpdate(float _Delta);

    void AttackStart();
    void AttackUpdate(float _Delta);

    void ChangeState(BossMonsterState _State);

    std::string CurState = "";

    void ChangeAnimationState(const std::string& _StateName);

protected:

private:
    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;

    void Start() override;

    void Update(float _Delta) override;

    GameEngineCollision* BodyCollision = nullptr;
    float4 BodyCollisionPos = float4{ 0 , 0 };
    float4 BodyCollisionScale = float4{ 150, 550 };

    GameEngineActor* Actor = nullptr;
    int BossHp = 100;

    int Count = 0;
};


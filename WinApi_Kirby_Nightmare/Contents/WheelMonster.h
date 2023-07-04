#pragma once
#include "Monster.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class WheelMonsterState
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

enum class WheelMonsterDir
{
    Right,
    Left,
};

class GameEngineRenderer;
class WheelMonster : public Monster
{
public:
    WheelMonster();
    ~WheelMonster();

    WheelMonster(const WheelMonster& _Other) = delete;
    WheelMonster(WheelMonster&& _Other) noexcept = delete;
    WheelMonster& operator=(const WheelMonster& _Other) = delete;
    WheelMonster& operator=(WheelMonster&& _Other) noexcept = delete;

    GameEngineRenderer* MainRenderer = nullptr;

    WheelMonsterState State = WheelMonsterState::Max;
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


    void ChangeState(WheelMonsterState _State);

    WheelMonsterDir Dir = WheelMonsterDir::Right;
    std::string CurState = "";

    void ChangeAnimationState(const std::string& _StateName);

protected:

    unsigned int GetWallCheck();
    void Movement(float _Delta);

private:
    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float Speed = 400.0f;

    void Start() override;

    void Update(float _Delta) override;

    GameEngineCollision* BodyCollision = nullptr;
    GameEngineCollision* DeathCollision = nullptr;
    float4 CollisionPos = float4{ 0 , -40 };
    float4 CollisionScale = float4{ 80, 80 };
    float4 DeathCollisionScale = float4{ 100, 100 };

    GameEngineActor* Actor = nullptr;

    class GameEngineSoundPlayer SoundEffect;
};


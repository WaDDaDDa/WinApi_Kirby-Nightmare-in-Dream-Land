#pragma once
#include "GravityActor.h"

enum class KirbyState
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
    StarIn,
    StarOut,
    FatIdle,
    FatWalk,
    FatJump,
    FatJumpTurn,
    FatFalling,
    FatFallingEnd,
    BreathOut,
    Swallow,
    Damage,
    FatDamage,
    Max, // 일반적으로 사용하지 않는 값.
};

enum class KirbyDir
{
    Right,
    Left,
};

class GameEngineRenderer;
class Kirby : public GravityActor
{
    friend class BurningKirby;
private:
    static Kirby* MainPlayer;

public:
    Kirby();
    ~Kirby();

    Kirby(const Kirby& _Other) = delete;
    Kirby(Kirby&& _Other) noexcept = delete;
    Kirby& operator=(const Kirby& _Other) = delete;
    Kirby& operator=(Kirby&& _Other) noexcept = delete;

    GameEngineRenderer* MainRenderer = nullptr;

    float4 GetMovePos()
    {
        return MovePos;
    }

    static void SetMainPlayer(Kirby* _MainPlayer)
    {
        MainPlayer = _MainPlayer;
    }

    static Kirby* GetMainPlayer()
    {
        return MainPlayer;
    }

    unsigned int GetWallCheck();

    void Movement(float _Delta);

    void Immune();
    void RenderSwitch();

    KirbyDir GetDir()
    {
        return Dir;
    }

protected:
    // 클래스로 만들어도 된다. 행동과 랜더.
    void ChangeState(KirbyState _State);
    void StateUpdate(float _Delta);

    void IdleStart();
    void DownIdleStart();
    void TackleStart();
    void WalkStart();
    void JumpStart();
    void JumpTurnStart();
    void FallingStart();
    void FallingEndStart();
    void RunStart();
    void FlyStart();
    void BreathInStart();
    virtual void AttackStartStart();
    virtual void AttackStart();
    void StarInStart();
    void StarOutStart();
    void FatIdleStart();
    void FatWalkStart();
    void FatJumpStart();
    void FatJumpTurnStart();
    void FatFallingStart();
    void FatFallingEndStart();
    void BreathOutStart();
    void SwallowStart();
    virtual void DamageStart();
    void FatDamageStart();

    void IdleUpdate(float _Delta);
    void DownIdleUpdate(float _Delta);
    void TackleUpdate(float _Delta);
    void WalkUpdate(float _Delta);
    void JumpUpdate(float _Delta);
    void JumpTurnUpdate(float _Delta);
    void FallingUpdate(float _Delta);
    void FallingEndUpdate(float _Delta);
    void RunUpdate(float _Delta);
    void FlyUpdate(float _Delta);
    void BreathInUpdate(float _Delta);
    virtual void AttackStartUpdate(float _Delta);
    virtual void AttackUpdate(float _Delta);
    void StarInUpdate(float _Delta);
    void StarOutUpdate(float _Delta);
    void FatIdleUpdate(float _Delta);
    void FatWalkUpdate(float _Delta);
    void FatJumpUpdate(float _Delta);
    void FatJumpTurnUpdate(float _Delta);
    void FatFallingUpdate(float _Delta);
    void FatFallingEndUpdate(float _Delta);
    void BreathOutUpdate(float _Delta);
    void SwallowUpdate(float _Delta);
    void DamageUpdate(float _Delta);
    void FatDamageUpdate(float _Delta);


    KirbyState State = KirbyState::Max;

    KirbyDir Dir = KirbyDir::Right;
    std::string CurState = "";

    void DirCheck();
    virtual void CameraFocus(float _Delta);
    virtual void ChangeAnimationState(const std::string& _StateName);

    GameEngineCollision* BodyCollision = nullptr;
    GameEngineCollision* AttackCollision = nullptr;

private:
    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float4 BodyCollisionPos = float4{ 0 , -40 };
    float4 BodyCollisionScale = float4{ 80, 80 };
    float4 AttackCollisionPos = float4{ 100 , -50 };
    float4 AttackCollisionScale = float4{ 100,80 };

    Abillity CurAbillity = Abillity::Normal;
    Abillity ChangeAbillity = Abillity::Normal;

    float Speed = 400.0f;
    float JumpPower = 800.0f;
    bool ImmuneValue = false;

    void Start() override;
    void Update(float _Delta) override;
    // void Render(float _Delta) override;

    void LevelStart() override;
};


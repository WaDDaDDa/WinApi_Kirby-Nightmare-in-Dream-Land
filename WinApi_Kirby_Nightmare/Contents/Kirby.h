#pragma once
#include "GravityActor.h"

enum class KirbyState
{
    Idle,
    Walk,
    Jump,
    JumpTurn,
    Falling,
    FallingEnd,
    Run,
    Fly,
    BreathIn,
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

    static Kirby* GetMainPlayer()
    {
        return MainPlayer;
    }

    unsigned int GetWallCheck();

    void Movement(float _Delta);

protected:
    // 클래스로 만들어도 된다. 행동과 랜더.
    void StateUpdate(float _Delta);

    void IdleStart();
    void WalkStart();
    void JumpStart();
    void JumpTurnStart();
    void FallingStart();
    void FallingEndStart();
    void RunStart();
    void FlyStart();
    void BreathInStart();

    void IdleUpdate(float _Delta);
    void WalkUpdate(float _Delta);
    void JumpUpdate(float _Delta);
    void JumpTurnUpdate(float _Delta);
    void FallingUpdate(float _Delta);
    void FallingEndUpdate(float _Delta);
    void RunUpdate(float _Delta);
    void FlyUpdate(float _Delta);
    void BreathInUpdate(float _Delta);

    void ChangeState(KirbyState _State);

    KirbyState State = KirbyState::Max;

    KirbyDir Dir = KirbyDir::Right;
    std::string CurState = "";

    void DirCheck();
    void CameraFocus();
    void ChangeAnimationState(const std::string& _StateName);

    GameEngineCollision* BodyCollsion = nullptr;

private:
    float4 MovePos = float4::ZERO;
    float4 CheckPos = float4::ZERO;
    float4 CollisionPos = float4{ 0 , -40 };
    float4 CollisionScale = float4{ 80, 80 };

    float Speed = 400.0f;
    float JumpPower = 800.0f;

    void Start() override;
    void Update(float _Delta) override;
    // void Render(float _Delta) override;

    void LevelStart() override;
};


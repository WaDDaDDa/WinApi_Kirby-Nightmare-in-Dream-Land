#pragma once
#include "GravityActor.h"

enum class KirbyState
{
    Idle,
    Walk,
    Jump,
    Run,
    Fly,
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

protected:
    // 클래스로 만들어도 된다. 행동과 랜더.
    void StateUpdate(float _Delta);

    void IdleStart();
    void WalkStart();
    void JumpStart();
    void RunStart();
    void FlyStart();

    void IdleUpdate(float _Delta);
    void WalkUpdate(float _Delta);
    void JumpUpdate(float _Delta);
    void RunUpdate(float _Delta);
    void FlyUpdate(float _Delta);

    void ChangeState(KirbyState _State);

    KirbyState State = KirbyState::Max;

    KirbyDir Dir = KirbyDir::Right;
    std::string CurState = "";

    void DirCheck();
    void CameraFocus();

    void ChangeAnimationState(const std::string& _StateName);


private:
    float4 MovePos = float4::ZERO;

    void Start() override;
    void Update(float _Delta) override;

    void LevelStart() override;
};


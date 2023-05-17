#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class KirbyState
{
    Idle,
    Run,
    Shoot,
    Max, // 일반적으로 사용하지 않는 값.
};

class GameEngineRenderer;
class Kirby : public GameEngineActor
{
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

protected:
    // 클래스로 만들어도 된다. 행동과 랜더.
    void StateUpdate(float _Delta);

    void IdleStart();
    void RunStart();
    void ShootStart();

    void IdleUpdate(float _Delta);
    void RunUpdate(float _Delta);
    void ShootUpdate(float _Delta);

    void ChangeState(KirbyState _State);

    KirbyState State = KirbyState::Max;

private:
    float4 MovePos = float4::ZERO;

    void Start() override;
    void Update(float _Delta) override;


};


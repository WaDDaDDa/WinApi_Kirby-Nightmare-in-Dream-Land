#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class KirbyState
{
    Idle,
    Run,
    Jump,
    Max, // �Ϲ������� ������� �ʴ� ��.
};

enum class KirbyDir
{
    Right,
    Left,
    Max,
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
    // Ŭ������ ���� �ȴ�. �ൿ�� ����.
    void StateUpdate(float _Delta);

    void IdleStart();
    void RunStart();
    void JumpStart();

    void IdleUpdate(float _Delta);
    void RunUpdate(float _Delta);
    void JumpUpdate(float _Delta);

    void ChangeState(KirbyState _State);

    KirbyState State = KirbyState::Max;

    KirbyDir Dir = KirbyDir::Right;
    std::string CurState = "";

    void DirCheck();

    void ChangeAnimationState(const std::string& _StateName);

private:
    float4 MovePos = float4::ZERO;

    void Start() override;
    void Update(float _Delta) override;


};


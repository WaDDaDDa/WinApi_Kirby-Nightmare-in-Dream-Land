#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Kirby : public GameEngineActor
{
public:
    Kirby();
    ~Kirby();

    Kirby(const Kirby& _Other) = delete;
    Kirby(Kirby&& _Other) noexcept = delete;
    Kirby& operator=(const Kirby& _Other) = delete;
    Kirby& operator=(Kirby&& _Other) noexcept = delete;

    float4 GetMovePos()
    {
        return MovePos;
    }

protected:

private:
    float4 MovePos = float4::ZERO;

    void Start() override;
    void Update(float _Delta) override;
    void Render() override;
    void Release() override;

};


#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Kirby.h"
#include <string>
#include <GameEnginePlatform/GameEngineSound.h>


class WheelEffect : public GameEngineActor
{
public:
    WheelEffect();
    ~WheelEffect();

    WheelEffect(const WheelEffect& _Other) = delete;
    WheelEffect(WheelEffect&& _Other) noexcept = delete;
    WheelEffect& operator=(const WheelEffect& _Other) = delete;
    WheelEffect& operator=(WheelEffect&& _Other) noexcept = delete;

protected:

private:

    class GameEngineRenderer* LeftRenderer = nullptr;
    GameEngineRenderer* LeftRenderer2 = nullptr;

    class GameEngineRenderer* RightRenderer = nullptr;
    GameEngineRenderer* RightRenderer2 = nullptr;

    void Start() override;
    void Update(float _Delta) override;

};


#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Kirby.h"
#include <string>
#include <GameEnginePlatform/GameEngineSound.h>


class FormChangeEffect : public GameEngineActor
{
public:
    FormChangeEffect();
    ~FormChangeEffect();

    FormChangeEffect(const FormChangeEffect& _Other) = delete;
    FormChangeEffect(FormChangeEffect&& _Other) noexcept = delete;
    FormChangeEffect& operator=(const FormChangeEffect& _Other) = delete;
    FormChangeEffect& operator=(FormChangeEffect&& _Other) noexcept = delete;

protected:

private:

    class GameEngineRenderer* Renderer = nullptr;

    void Start() override;
    void Update(float _Delta) override;

};


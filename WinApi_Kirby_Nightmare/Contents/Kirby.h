#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Kirby : public GameEngineActor
{
public:
    Kirby();
    ~Kirby();

    Kirby(const Kirby& _Other) = delete;
    Kirby(Kirby&& _Other) = delete;
    Kirby& operator=(const Kirby& _Other) = delete;
    Kirby& operator=(Kirby&& _Other) = delete;

protected:

private:
    void Start() override;
    void Update(float _Delta) override;
    void Render() override;
    void Release() override;
};


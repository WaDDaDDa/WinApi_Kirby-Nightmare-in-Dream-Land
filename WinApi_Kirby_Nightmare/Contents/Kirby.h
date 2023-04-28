#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Kirby : public GameEngineActor
{
public:
    Kirby();
    ~Kirby();

    Kirby& operator=(const Kirby& _Other) = delete;
    Kirby& operator=(const Kirby&& _Other) = delete;
    Kirby(const Kirby& _Other) = delete;
    Kirby(const Kirby&& _Other) = delete;

protected:

private:
    void Start() override;
    void Update() override;
    void Render() override;
    void Release() override;
};


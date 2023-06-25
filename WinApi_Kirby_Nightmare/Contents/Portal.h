#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Portal : public GameEngineActor
{
public:
    Portal();
    ~Portal();

    Portal(const Portal& _Other) = delete;
    Portal(Portal&& _Other) noexcept = delete;
    Portal& operator=(const Portal& _Other) = delete;
    Portal& operator=(Portal&& _Other) noexcept = delete;

    class GameEngineCollision* BodyCollision = nullptr;
    class GameEngineRenderer* Door = nullptr;

protected:

private:
    float4 DoorPos = float4{ 500 , 0 };
    float4 BodyCollisionScale = float4{ 100 , 100 };
    void Start() override;
    void Update(float _Delta) override;
};


#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GravityActor : public GameEngineActor
{
public:
    GravityActor();
    ~GravityActor();

    GravityActor(const GravityActor& _Other) = delete;
    GravityActor(GravityActor&& _Other) noexcept = delete;
    GravityActor& operator=(const GravityActor& _Other) = delete;
    GravityActor& operator=(GravityActor&& _Other) noexcept = delete;

    void Gravity(float _Delta);

  

    void GravityOff()
    {
        IsGravity = false;
    }

    void SetGroundTexture(const std::string& _GroundTextureName);

protected:

private:

    class GameEngineWindowTexture* GroundTexture = nullptr;

    bool IsGravity = true;

    float GravityPower = 0.01f;

    float4 GravityVector = float4::ZERO;

};


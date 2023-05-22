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

    void GravityReset()
    {
        GravityVector = float4::ZERO;
    }

    void GravityOff()
    {
        IsGravity = false;
    }
    float4 GetGravityVector()
    {
        return GravityVector;
    }

    void SetGroundTexture(const std::string& _GroundTextureName);

    int GetGroundColor(unsigned int _DefaultColor = RGB(255, 255, 255), float4 _Pos = float4::ZERO);

    void GroundCheck(float _Delta);

protected:

private:

    class GameEngineWindowTexture* GroundTexture = nullptr;

    bool IsGravity = true;

    float GravityPower = 2.0f;

    float4 GravityVector = float4::ZERO;

};


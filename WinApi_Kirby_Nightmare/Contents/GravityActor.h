#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
class GameEngineWindowTexture;
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

    void SetGroundTexture(GameEngineWindowTexture* _GroundTextureName)
    {
        GroundTexture = _GroundTextureName;
    }

    GameEngineWindowTexture* GetGroundTexture()
    {
        return GroundTexture;
    }

    int GetGroundColor(unsigned int _DefaultColor = RGB(255, 255, 255), float4 _Pos = float4::ZERO);

    void GroundCheck(float _Delta);

    float4 LeftCheck = float4{ -30 , 0 };
    float4 RightCheck = float4{ 30 , 0 };

    void SetGravityVector(float4 _GravityVector)
    {
        GravityVector = _GravityVector;
    }


protected:


private:

    GameEngineWindowTexture* GroundTexture = nullptr;

    bool IsGravity = true;

    float GravityPower = 1000.0f;

    float4 GravityVector = float4::ZERO;

};


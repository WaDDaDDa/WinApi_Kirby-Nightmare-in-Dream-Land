#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class DesertLevel2 : public GameEngineLevel
{
public:
    DesertLevel2();
    ~DesertLevel2();

    DesertLevel2& operator=(const DesertLevel2& _Other) = delete;
    DesertLevel2& operator=(const DesertLevel2&& _Other) = delete;
    DesertLevel2(const DesertLevel2& _Other) = delete;
    DesertLevel2(const DesertLevel2&& _Other) = delete;

protected:
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    void Start() override;
    void Update(float _Delta) override;
    void Release() override;

    class BackGround* CurBackGround = nullptr;

    class Stage* StagePtr = nullptr;
    class Portal* MainPortal = nullptr;

    float4 StartPos = float4{ 165 , 901 };
    float4 PortalPos = float4{ 5540, 400 };
};


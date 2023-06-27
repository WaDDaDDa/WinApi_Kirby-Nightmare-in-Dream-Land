#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class DesertLevel : public GameEngineLevel
{
public:
    DesertLevel();
    ~DesertLevel();

    DesertLevel& operator=(const DesertLevel& _Other) = delete;
    DesertLevel& operator=(const DesertLevel&& _Other) = delete;
    DesertLevel(const DesertLevel& _Other) = delete;
    DesertLevel(const DesertLevel&& _Other) = delete;

protected:
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    void Start() override;
    void Update(float _Delta) override;
    void Release() override;

    GameEngineSoundPlayer BGMPlayer;
    class BackGround* CurBackGround = nullptr;

    class Stage* StagePtr = nullptr;
    class Portal* MainPortal = nullptr;

    float4 StartPos = float4{ 360 , 350 };
    float4 PortalPos = float4{ 4060, 445 };
};


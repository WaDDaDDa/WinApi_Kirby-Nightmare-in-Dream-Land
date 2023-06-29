#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class MainHubLevel : public GameEngineLevel
{
public:
    MainHubLevel();
    ~MainHubLevel();

    MainHubLevel(const MainHubLevel& _Other) = delete;
    MainHubLevel(MainHubLevel&& _Other) noexcept = delete;
    MainHubLevel& operator=(const MainHubLevel& _Other) = delete;
    MainHubLevel& operator=(MainHubLevel&& _Other) noexcept = delete;

protected:
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;
    
private:
    void Start() override;
    void Update(float _Delta) override;
    void Release() override;
    void CameraFocus();

    class Stage* StagePtr = nullptr;
    class BackGround* CurBackGround = nullptr;

    //GameEngineSoundPlayer BGMPlayer;

    float4 StartPlayerPos = float4{ 700 , 900 };

    class Portal* Stage1Portal = nullptr;
    float4 Stage1PortalPos = float4{ 448, 1040 };

    Portal* Stage2Portal = nullptr;
    float4 Stage2PortalPos = float4{ 960, 1170 };


    Portal* Stage3Portal = nullptr;
    float4 Stage3PortalPos = float4{ 704, 850 };

    Portal* Stage4Portal = nullptr;
    float4 Stage4PortalPos = float4{ 960, 593 };

    Portal* Stage5Portal = nullptr;
    float4 Stage5PortalPos = float4{ 1282, 785 };

    Portal* Stage6Portal = nullptr;
    float4 Stage6PortalPos = float4{ 1603, 975 };

    Portal* Stage7Portal = nullptr;
    float4 Stage7PortalPos = float4{ 1793, 465 };

    Portal* Stage8Portal = nullptr;
    float4 Stage8PortalPos = float4{ 1794, 210 };
};

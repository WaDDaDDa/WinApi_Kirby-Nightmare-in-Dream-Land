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

    GameEngineSoundPlayer BGMPlayer;

    float4 StartPlayerPos = float4{ 700 , 900 };

    class Portal* Stage1Portal = nullptr;
    Portal* Stage2Portal = nullptr;
};

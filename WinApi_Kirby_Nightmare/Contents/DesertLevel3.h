#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class DesertLevel3 : public GameEngineLevel
{
public:
    DesertLevel3();
    ~DesertLevel3();

    DesertLevel3& operator=(const DesertLevel3& _Other) = delete;
    DesertLevel3& operator=(const DesertLevel3&& _Other) = delete;
    DesertLevel3(const DesertLevel3& _Other) = delete;
    DesertLevel3(const DesertLevel3&& _Other) = delete;

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

    float4 StartPos = float4{ 360 , 4500 };
};


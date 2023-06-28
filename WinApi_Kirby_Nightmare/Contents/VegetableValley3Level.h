#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class VegetableValley3Level : public GameEngineLevel
{
public:
    VegetableValley3Level();
    ~VegetableValley3Level();

    VegetableValley3Level& operator=(const VegetableValley3Level& _Other) = delete;
    VegetableValley3Level& operator=(const VegetableValley3Level&& _Other) = delete;
    VegetableValley3Level(const VegetableValley3Level& _Other) = delete;
    VegetableValley3Level(const VegetableValley3Level&& _Other) = delete;

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
    float4 StartPos = float4{ 330, 640 };
    float4 PortalPos = float4{ 3940, 450 };

};


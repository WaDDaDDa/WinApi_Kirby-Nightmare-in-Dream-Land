#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class VegetableValley2Level : public GameEngineLevel
{
public:
    VegetableValley2Level();
    ~VegetableValley2Level();

    VegetableValley2Level& operator=(const VegetableValley2Level& _Other) = delete;
    VegetableValley2Level& operator=(const VegetableValley2Level&& _Other) = delete;
    VegetableValley2Level(const VegetableValley2Level& _Other) = delete;
    VegetableValley2Level(const VegetableValley2Level&& _Other) = delete;

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
};


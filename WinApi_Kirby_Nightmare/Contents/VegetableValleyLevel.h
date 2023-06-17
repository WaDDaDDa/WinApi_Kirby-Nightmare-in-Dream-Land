#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class VegetableValleyLevel : public GameEngineLevel
{
public:
    VegetableValleyLevel();
    ~VegetableValleyLevel();

    VegetableValleyLevel& operator=(const VegetableValleyLevel& _Other) = delete;
    VegetableValleyLevel& operator=(const VegetableValleyLevel&& _Other) = delete;
    VegetableValleyLevel(const VegetableValleyLevel& _Other) = delete;
    VegetableValleyLevel(const VegetableValleyLevel&& _Other) = delete;

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


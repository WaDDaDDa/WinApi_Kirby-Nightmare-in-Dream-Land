#pragma once
#include <GameEngineCore/GameEngineLevel.h>

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
    void Render() override;
    void Release() override;

    class Kirby* LevelPlayer = nullptr;
    class Stage* StagePtr = nullptr;
};


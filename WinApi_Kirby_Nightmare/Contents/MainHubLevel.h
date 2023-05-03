#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class MainHubLevel : public GameEngineLevel
{
public:
    MainHubLevel();
    ~MainHubLevel();

    MainHubLevel& operator=(const MainHubLevel& _Other) = delete;
    MainHubLevel& operator=(const MainHubLevel&& _Other) = delete;
    MainHubLevel(const MainHubLevel& _Other) = delete;
    MainHubLevel(const MainHubLevel&& _Other) = delete;

protected:

private:
    void Start() override;
    void Update(float _Delta) override;
    void Render() override;
    void Release() override;
};


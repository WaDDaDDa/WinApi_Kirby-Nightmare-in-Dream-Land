#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

class BossLevel : public GameEngineLevel
{
public:
    BossLevel();
    ~BossLevel();

    BossLevel& operator=(const BossLevel& _Other) = delete;
    BossLevel& operator=(const BossLevel&& _Other) = delete;
    BossLevel(const BossLevel& _Other) = delete;
    BossLevel(const BossLevel&& _Other) = delete;

protected:
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    void Start() override;
    void Update(float _Delta) override;
    void Release() override;

    class BackGround* CurBackGround = nullptr;

    class Stage* StagePtr = nullptr;

    float4 StartPos = float4{ 100 , 60 };

    class BossMonster* WhispyWoods = nullptr;

    class BossUIManager* BUI = nullptr;

    bool Once = false;
};


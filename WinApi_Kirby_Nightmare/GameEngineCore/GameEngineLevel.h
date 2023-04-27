#pragma once
#include <GameEngineCore/GameEngineObject.h>

// 화면 혹은 장면을 표현. ex)타이틀 장면, 플레이 장면, 엔딩 장면
class GameEngineLevel : public GameEngineObject
{
public:
    GameEngineLevel();
    ~GameEngineLevel();

    GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
    GameEngineLevel& operator=(const GameEngineLevel&& _Other) = delete;
    GameEngineLevel(const GameEngineLevel& _Other) = delete;
    GameEngineLevel(const GameEngineLevel&& _Other) = delete;

protected:

private:

};


#pragma once
#include <GameEngineCore/GameEngineObject.h>

// 화면안에 존재하는 모든 것.  좌표가 있다면 엑터로 표현.
class GameEngineActor : public GameEngineObject
{
public:
    GameEngineActor();
    ~GameEngineActor();

    GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
    GameEngineActor& operator=(const GameEngineActor&& _Other) = delete;
    GameEngineActor(const GameEngineActor& _Other) = delete;
    GameEngineActor(const GameEngineActor&& _Other) = delete;

protected:

private:

};


#pragma once
#include <GameEngineCore/GameEngineObject.h>

// ȭ��ȿ� �����ϴ� ��� ��.  ��ǥ�� �ִٸ� ���ͷ� ǥ��.
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


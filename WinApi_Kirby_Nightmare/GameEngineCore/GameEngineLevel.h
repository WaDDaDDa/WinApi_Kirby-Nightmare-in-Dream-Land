#pragma once
#include <GameEngineCore/GameEngineObject.h>

// ȭ�� Ȥ�� ����� ǥ��. ex)Ÿ��Ʋ ���, �÷��� ���, ���� ���
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


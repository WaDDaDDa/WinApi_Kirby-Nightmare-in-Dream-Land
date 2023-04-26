#pragma once
class GameEngineCore
{
public:
    GameEngineCore();
    ~GameEngineCore();

    GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
    GameEngineCore& operator=(const GameEngineCore&& _Other) = delete;
    GameEngineCore(const GameEngineCore& _Other) = delete;
    GameEngineCore(const GameEngineCore&& _Other) = delete;

protected:

private:

};


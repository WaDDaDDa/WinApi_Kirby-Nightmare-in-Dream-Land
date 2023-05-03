#pragma once
#include <string>
#include <filesystem> // c++ 17�������ĺ��� ����Ҽ��ִ�.

// ���ϰ�θ� �����ϱ����� ��ü.
class GameEnginePath
{
public:
    GameEnginePath();
    ~GameEnginePath();

    GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
    GameEnginePath& operator=(const GameEnginePath&& _Other) = delete;
    GameEnginePath(const GameEnginePath& _Other) = delete;
    GameEnginePath(const GameEnginePath&& _Other) = delete;

    void GetCurrentPath();

protected:

private:
    std::filesystem::path Path;

};


#pragma once
#include <string>
#include <filesystem> // c++ 17버전이후부터 사용할수있다.

// 파일경로를 관리하기위한 객체.
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


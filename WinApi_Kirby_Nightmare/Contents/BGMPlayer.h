#pragma once
#include <GameEnginePlatform/GameEngineSound.h>

class BGMPlayer
{
public:
    BGMPlayer();
    ~BGMPlayer();

    BGMPlayer(const BGMPlayer& _Other) = delete;
    BGMPlayer(BGMPlayer&& _Other) noexcept = delete;
    BGMPlayer& operator=(const BGMPlayer& _Other) = delete;
    BGMPlayer& operator=(BGMPlayer&& _Other) noexcept = delete;

    static void SetBGM(const std::string& _Name)
    {
        BGM = GameEngineSound::SoundPlay(_Name, 200);
        BGMName = _Name;
    }

    static void StopBGM()
    {
        BGM.Stop();
    }

    static void ChangeBGM(const std::string& _Name, int _Loop = 200)
    {
        if (BGMName == _Name)
        {
            return;
        }
        BGM.Stop();
        BGM = GameEngineSound::SoundPlay(_Name, _Loop);
        BGMName = _Name;
    }

protected:

private:
    static class GameEngineSoundPlayer BGM;
    static std::string BGMName;
};


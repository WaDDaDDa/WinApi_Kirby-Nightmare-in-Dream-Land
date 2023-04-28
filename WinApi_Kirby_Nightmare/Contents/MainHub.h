#pragma once
#include <GameEngineCore/GameEngineCore.h>

class MainHub : public CoreProcess
{
public:
    MainHub();
    ~MainHub();

    MainHub& operator=(const MainHub& _Other) = delete;
    MainHub& operator=(const MainHub&& _Other) = delete;
    MainHub(const MainHub& _Other) = delete;
    MainHub(const MainHub&& _Other) = delete;

protected:

private:
    void Start() override;

    // 행동한고.
    void Update() override;

    // 그려지고.
    void Render() override;

    // 정리된다.
    void Release() override;
};


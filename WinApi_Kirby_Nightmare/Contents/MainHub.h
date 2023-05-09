#pragma once
#include <GameEngineCore/GameEngineCore.h>

class MainHub : public CoreProcess
{
public:
    MainHub();
    ~MainHub();

    MainHub(const MainHub& _Other) = delete;
    MainHub(MainHub&& _Other) noexcept = delete;
    MainHub& operator=(const MainHub& _Other) = delete;
    MainHub& operator=(MainHub&& _Other) noexcept = delete;

protected:

private:
    void Start() override;

    // 행동한고.
    void Update(float _Delta) override;

    // 그려지고.
    void Render() override;

    // 정리된다.
    void Release() override;
};


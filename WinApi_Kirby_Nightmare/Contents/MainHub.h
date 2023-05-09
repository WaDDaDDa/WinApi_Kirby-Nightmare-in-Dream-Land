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

    // �ൿ�Ѱ�.
    void Update(float _Delta) override;

    // �׷�����.
    void Render() override;

    // �����ȴ�.
    void Release() override;
};


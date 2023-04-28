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

    // �ൿ�Ѱ�.
    void Update() override;

    // �׷�����.
    void Render() override;

    // �����ȴ�.
    void Release() override;
};


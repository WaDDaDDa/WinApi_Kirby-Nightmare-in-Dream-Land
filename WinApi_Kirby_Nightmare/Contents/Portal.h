#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PortalState
{
    Close,
    Opening,
    Open,
    Max,
};

class Portal : public GameEngineActor
{
public:
    Portal();
    ~Portal();

    Portal(const Portal& _Other) = delete;
    Portal(Portal&& _Other) noexcept = delete;
    Portal& operator=(const Portal& _Other) = delete;
    Portal& operator=(Portal&& _Other) noexcept = delete;

    class GameEngineCollision* BodyCollision = nullptr;
    class GameEngineRenderer* Door = nullptr;
    class GameEngineRenderer* SubDoor = nullptr;

    void SetCurLevel(std::string _CurLevel)
    {
        CurLevel = _CurLevel;
    }

protected:

    void ChangeAnimationState(const std::string& _StateName);

    void ChangeState(PortalState _State);

    void StateUpdate(float _Delta);

    void CloseStart();
    void CloseUpdate(float _Delta);

    void OpeningStart();
    void OpeningUpdate(float _Delta);

    void OpenStart();
    void OpenUpdate(float _Delta);

private:
    std::string CurState = "";
    std::string CurLevel = "";
    PortalState State = PortalState::Max;

    float4 DoorPos = float4{ 500 , 0 };
    float4 BodyCollisionScale = float4{ 100 , 100 };
    void Start() override;
    void Update(float _Delta) override;
};


#pragma once
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include <list>
#include <string>
#include <map>


// Level이란. 공간을 의미한다.
// 내가 MainPub이라는 Level에서는 그에맞는 맵이있을수있고, 출연할 플레이어와, 몬스터, 배경이 있다.
// 모든 Actor들이 Level에 생성되고 움직이므로 Level에서 관리를 하는것이 용이할수있다.
// 이 모든것을 준비해야하는 것이 레벨이다.
// 화면 혹은 장면을 표현. ex)타이틀 장면, 플레이 장면, 엔딩 장면
class GameEngineCamera;
class GameEngineCollision;
class GameEngineLevel : public GameEngineObject
{
    friend class GameEngineCollision;
    friend class GameEngineActor;
    friend class GameEngineCore; //GameEngineCore에게는 나의기능을 쓸수있게 하겠다.

public:
    GameEngineLevel();
    ~GameEngineLevel();

    GameEngineLevel(const GameEngineLevel& _Other) = delete;
    GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
    GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
    GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

    template<typename ActorType, typename EnumType>
    ActorType* CreateActor(EnumType _Order)
    {
        return CreateActor<ActorType>(static_cast<int>(_Order));
    }

    template<typename ActorType>
    ActorType* CreateActor(int _Order = 0)
    {
        // map에서 map[] 오퍼레이터가 있다.  의미는 map[first]의 값을 리턴해달라.
        // 리턴할 first인 노드가 없다면 만들어서 리턴하라는 의미이다.
        std::list<GameEngineActor*>& GroupList = AllActors[_Order];
        GameEngineActor* NewActor = new ActorType();
        ActorInit(NewActor, _Order);
        GroupList.push_back(NewActor);

        // GameEnigneActor가 최상위 Actor이고 ActorType은 그 하위이다.
        // GameEngineActor포인터로 new ActorType을 받은건 업캐스팅 한것이지만.
        // 리턴 값은 ActorType*이기때문에 GameEngineActor를 그대로 리턴할수 없다.
        // 따라서 Dynamic_cast를 통한 다운캐스팅으로 GameEngineActor*를 ActorType*로 리턴할수있다.
        return dynamic_cast<ActorType*>(NewActor);
    }

    GameEngineCamera* GetMainCamera()
    {
        return MainCamera;
    }

    GameEngineCamera* GetUICamera()
    {
        return UICamera;
    }

    static void CollisionDebugRenderSwitch()
    {
        IsCollisionDebugRender = !IsCollisionDebugRender;
    }

    void OverCheck(GameEngineLevel* _PrevLevel);

protected:
    virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
    virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

private:
    GameEngineCamera* MainCamera;
    GameEngineCamera* UICamera;

    static bool IsCollisionDebugRender;

	std::map<int, std::list<GameEngineActor*>> AllActors;
	std::map<int, std::list<GameEngineCollision*>> AllCollision;

	void ActorInit(GameEngineActor* _Actor, int _Order);

    // 레벨에서 엑터가 레벨이 시작되고 끝났음을 안다.
    void ActorLevelStart();
    void ActorLevelEnd();

	void ActorUpdate(float _Delta);
	void ActorRender(float _Delta);
    void ActorRelease();

    void CollisionOverRelease();
    void CollisionRelease();
};


#pragma once
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineActor.h>
#include <list>
#include <string>
#include <map>

// Level이란. 공간을 의미한다.
// 내가 MainPub이라는 Level에서는 그에맞는 맵이있을수있고, 출연할 플레이어와, 몬스터, 배경이 있다.
// 모든 Actor들이 Level에 생성되고 움직이므로 Level에서 관리를 하는것이 용이할수있다.
// 이 모든것을 준비해야하는 것이 레벨이다.
// 화면 혹은 장면을 표현. ex)타이틀 장면, 플레이 장면, 엔딩 장면
class GameEngineLevel : public GameEngineObject
{
    friend class GameEngineCore; //GameEngineCore에게는 나의기능을 쓸수있게 하겠다.

public:
    GameEngineLevel();
    ~GameEngineLevel();

    GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
    GameEngineLevel& operator=(const GameEngineLevel&& _Other) = delete;
    GameEngineLevel(const GameEngineLevel& _Other) = delete;
    GameEngineLevel(const GameEngineLevel&& _Other) = delete;


    template<typename ActorType>
    void CreateActor(int _Order = 0)
    {
        // map에서 map[] 오퍼레이터가 있다.  의미는 map[first]의 값을 리턴해달라.
        // 리턴할 first인 노드가 없다면 만들어서 리턴하라는 의미이다.
        std::list<GameEngineActor*>& GroupList = AllActors[_Order];
        GameEngineActor* NewActor = new ActorType();
        ActorInit(NewActor);
        GroupList.push_back(NewActor);
    }

protected:

private:
	// 맵
    // 플레이어
    // 몬스터

    // -10번 std::list<> 액터 액터 액터 액터 
    // 0번 std::list<> 액터 액터 액터 액터
    // 1번 std::list<> 액터 액터 액터 액터
    // 모든 Actor들을 GameEngineActor가 있는 리스트를 Map으로 관리한다.
    // Actor가 아닌 Actor들이 들어있는 Actor그룹을 관리하는것이다.
	std::map<int, std::list<GameEngineActor*>> AllActors;

	void ActorInit(GameEngineActor* _Actor);

	void ActorUpdate(float _Delta);
	void ActorRender();
};


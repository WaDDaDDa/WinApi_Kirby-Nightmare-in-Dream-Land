#pragma once
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include <list>
#include <string>
#include <map>


// Level�̶�. ������ �ǹ��Ѵ�.
// ���� MainPub�̶�� Level������ �׿��´� �����������ְ�, �⿬�� �÷��̾��, ����, ����� �ִ�.
// ��� Actor���� Level�� �����ǰ� �����̹Ƿ� Level���� ������ �ϴ°��� �����Ҽ��ִ�.
// �� ������ �غ��ؾ��ϴ� ���� �����̴�.
// ȭ�� Ȥ�� ����� ǥ��. ex)Ÿ��Ʋ ���, �÷��� ���, ���� ���
class GameEngineCamera;
class GameEngineCollision;
class GameEngineLevel : public GameEngineObject
{
    friend class GameEngineCollision;
    friend class GameEngineActor;
    friend class GameEngineCore; //GameEngineCore���Դ� ���Ǳ���� �����ְ� �ϰڴ�.

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
        // map���� map[] ���۷����Ͱ� �ִ�.  �ǹ̴� map[first]�� ���� �����ش޶�.
        // ������ first�� ��尡 ���ٸ� ���� �����϶�� �ǹ��̴�.
        std::list<GameEngineActor*>& GroupList = AllActors[_Order];
        GameEngineActor* NewActor = new ActorType();
        ActorInit(NewActor, _Order);
        GroupList.push_back(NewActor);

        // GameEnigneActor�� �ֻ��� Actor�̰� ActorType�� �� �����̴�.
        // GameEngineActor�����ͷ� new ActorType�� ������ ��ĳ���� �Ѱ�������.
        // ���� ���� ActorType*�̱⶧���� GameEngineActor�� �״�� �����Ҽ� ����.
        // ���� Dynamic_cast�� ���� �ٿ�ĳ�������� GameEngineActor*�� ActorType*�� �����Ҽ��ִ�.
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

    // �������� ���Ͱ� ������ ���۵ǰ� �������� �ȴ�.
    void ActorLevelStart();
    void ActorLevelEnd();

	void ActorUpdate(float _Delta);
	void ActorRender(float _Delta);
    void ActorRelease();

    void CollisionOverRelease();
    void CollisionRelease();
};


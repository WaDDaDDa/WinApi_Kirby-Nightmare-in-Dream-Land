#pragma once
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineActor.h>
#include <list>
#include <string>
#include <map>

// Level�̶�. ������ �ǹ��Ѵ�.
// ���� MainPub�̶�� Level������ �׿��´� �����������ְ�, �⿬�� �÷��̾��, ����, ����� �ִ�.
// ��� Actor���� Level�� �����ǰ� �����̹Ƿ� Level���� ������ �ϴ°��� �����Ҽ��ִ�.
// �� ������ �غ��ؾ��ϴ� ���� �����̴�.
// ȭ�� Ȥ�� ����� ǥ��. ex)Ÿ��Ʋ ���, �÷��� ���, ���� ���
class GameEngineLevel : public GameEngineObject
{
    friend class GameEngineCore; //GameEngineCore���Դ� ���Ǳ���� �����ְ� �ϰڴ�.

public:
    GameEngineLevel();
    ~GameEngineLevel();

    GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
    GameEngineLevel& operator=(const GameEngineLevel&& _Other) = delete;
    GameEngineLevel(const GameEngineLevel& _Other) = delete;
    GameEngineLevel(const GameEngineLevel&& _Other) = delete;


    template<typename ActorType>
    ActorType* CreateActor(int _Order = 0)
    {
        // map���� map[] ���۷����Ͱ� �ִ�.  �ǹ̴� map[first]�� ���� �����ش޶�.
        // ������ first�� ��尡 ���ٸ� ���� �����϶�� �ǹ��̴�.
        std::list<GameEngineActor*>& GroupList = AllActors[_Order];
        GameEngineActor* NewActor = new ActorType();
        ActorInit(NewActor);
        GroupList.push_back(NewActor);

        // GameEnigneActor�� �ֻ��� Actor�̰� ActorType�� �� �����̴�.
        // GameEngineActor�����ͷ� new ActorType�� ������ ��ĳ���� �Ѱ�������.
        // ���� ���� ActorType*�̱⶧���� GameEngineActor�� �״�� �����Ҽ� ����.
        // ���� Dynamic_cast�� ���� �ٿ�ĳ�������� GameEngineActor*�� ActorType*�� �����Ҽ��ִ�.
        return dynamic_cast<ActorType*>(NewActor);
    }

protected:

private:
	// ��
    // �÷��̾�
    // ����

    // -10�� std::list<> ���� ���� ���� ���� 
    // 0�� std::list<> ���� ���� ���� ����
    // 1�� std::list<> ���� ���� ���� ����
    // ��� Actor���� GameEngineActor�� �ִ� ����Ʈ�� Map���� �����Ѵ�.
    // Actor�� �ƴ� Actor���� ����ִ� Actor�׷��� �����ϴ°��̴�.
	std::map<int, std::list<GameEngineActor*>> AllActors;

	void ActorInit(GameEngineActor* _Actor);

	void ActorUpdate(float _Delta);
	void ActorRender();
};


#include "GameEngineLevel.h"


GameEngineLevel::GameEngineLevel()
{

}

GameEngineLevel::~GameEngineLevel()
{
	// �ش� ������ �Ҹ�ɶ� ��� Actor�׷� ���� delete��Ų��.
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			if (nullptr != _Actor)
			{
				delete _Actor;
				_Actor = nullptr;
			}
		}
	}
}


void GameEngineLevel::ActorInit(GameEngineActor* _Actor)
{
	// Actor�� �غ񹰽���
	_Actor->Start();
}

void GameEngineLevel::ActorUpdate()
{
	// Actor�׷��� ������Ʈ.
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			_Actor->Update();
		}
	}
}
void GameEngineLevel::ActorRender()
{
	//Actor���� ����.
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			_Actor->Render();
		}
	}
}
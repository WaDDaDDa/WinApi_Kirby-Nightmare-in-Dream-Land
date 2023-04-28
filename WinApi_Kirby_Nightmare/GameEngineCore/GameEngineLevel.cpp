#include "GameEngineLevel.h"


GameEngineLevel::GameEngineLevel()
{

}

GameEngineLevel::~GameEngineLevel()
{
	// 해당 레벨이 소멸될때 모든 Actor그룹 들을 delete시킨다.
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
	// Actor의 준비물실행
	_Actor->Start();
}

void GameEngineLevel::ActorUpdate()
{
	// Actor그룹의 업데이트.
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
	//Actor들의 렌더.
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			_Actor->Render();
		}
	}
}
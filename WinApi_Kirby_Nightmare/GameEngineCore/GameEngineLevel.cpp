#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineLevel::GameEngineLevel()
{
	MainCamera = new GameEngineCamera();
	UICamera = new GameEngineCamera();
}

GameEngineLevel::~GameEngineLevel()
{
	if (nullptr != MainCamera)
	{
		delete MainCamera;
		MainCamera = nullptr;
	}

	if (nullptr != UICamera)
	{
		delete UICamera;
		UICamera = nullptr;
	}


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


void GameEngineLevel::ActorInit(GameEngineActor* _Actor, int _Order)
{
	// Actor의 준비물실행
	_Actor->Level = this;
	_Actor->SetOrder(_Order);
	_Actor->Start();
}

void GameEngineLevel::ActorUpdate(float _Delta)
{
	// Actor그룹의 업데이트.
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}
			_Actor->AddLiveTime(_Delta);
			_Actor->Update(_Delta);
		}
	}
}

void GameEngineLevel::ActorRender(float _Delta)
{
	MainCamera->Render(_Delta);

	//Actor들의 렌더.
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}

			_Actor->Render();
		}
	}
}

// 레벨에서 엑터를 관리하고 있기때문에 엑터를 지우는것도 레벨에서 관리한다.
void GameEngineLevel::ActorRelease()
{
	MainCamera->Release();

	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = AllActors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = AllActors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& Group = GroupStartIter->second;

		std::list<GameEngineActor*>::iterator ObjectStartIter = Group.begin();
		std::list<GameEngineActor*>::iterator ObjectEndIter = Group.end();

		for (; ObjectStartIter != ObjectEndIter; )
		{
			GameEngineActor* Actor = *ObjectStartIter;
			if (false == Actor->IsDeath())
			{
				Actor->ActorRelease(); //여기서 문제가 생긴다.
				++ObjectStartIter;
				continue;
			}

			if (nullptr == Actor)
			{
				MsgBoxAssert("nullptr인 액터가 레벨의 리스트에 들어가 있었습니다.");
				continue;
			}

			delete Actor;
			Actor = nullptr;

			//                      i
			// [s] [a] [a]     [a] [e]
			ObjectStartIter = Group.erase(ObjectStartIter);
		}
	}
}
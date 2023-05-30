#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineCollision.h"

bool GameEngineLevel::IsCollisionDebugRender = false;

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

	UICamera->Render(_Delta);

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

			_Actor->Render(_Delta);
		}
	}

	if (true == IsCollisionDebugRender)
	{
		for (const std::pair<int, std::list<GameEngineCollision*>>& Pair : AllCollision)
		{
			const std::list < GameEngineCollision*>& Group = Pair.second;

			for (GameEngineCollision* Collision : Group)
			{
				Collision->DebugRender();
			}

		}
	}
}

// 레벨에서 엑터를 관리하고 있기때문에 엑터를 지우는것도 레벨에서 관리한다.
void GameEngineLevel::ActorRelease()
{
	MainCamera->Release();

	// 콜리전의 릴리즈
	{
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = AllCollision.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = AllCollision.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineCollision*>& Group = GroupStartIter->second;

			std::list<GameEngineCollision*>::iterator ObjectStartIter = Group.begin();
			std::list<GameEngineCollision*>::iterator ObjectEndIter = Group.end();

			for (; ObjectStartIter != ObjectEndIter; )
			{
				GameEngineCollision* Object = *ObjectStartIter;
				if (false == Object->IsDeath())
				{
					++ObjectStartIter;
					continue;
				}

				ObjectStartIter = Group.erase(ObjectStartIter);

			}
		}
	}
	// 액터의 릴리즈
	{
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
}

void GameEngineLevel::ActorLevelStart() 
{
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			_Actor->LevelStart();
		}
	}
}

void GameEngineLevel::ActorLevelEnd()
{
	for (const std::pair<int, std::list<GameEngineActor*>>& _Pair : AllActors)
	{
		const std::list<GameEngineActor*>& Group = _Pair.second;

		for (GameEngineActor* _Actor : Group)
		{
			_Actor->LevelEnd();
		}
	}
}

void GameEngineLevel::CollisionOverRelease()
{
	{
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = AllCollision.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = AllCollision.end();

		// 눈꼽 만큼이라도 연산을 줄이려는 거죠.

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineCollision*>& Group = GroupStartIter->second;

			std::list<GameEngineCollision*>::iterator ObjectStartIter = Group.begin();
			std::list<GameEngineCollision*>::iterator ObjectEndIter = Group.end();

			for (; ObjectStartIter != ObjectEndIter; )
			{
				GameEngineCollision* Object = *ObjectStartIter;
				// 레벨이 끝나면 콜리젼을 지우는것
				if (false == Object->GetActor()->IsLevelOver())
				{
					++ObjectStartIter;
					continue;
				}

				ObjectStartIter = Group.erase(ObjectStartIter);
			}
		}
	}
}

void GameEngineLevel::CollisionRelease()
{
	{
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = AllCollision.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = AllCollision.end();

		// 눈꼽 만큼이라도 연산을 줄이려는 거죠.

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineCollision*>& Group = GroupStartIter->second;

			std::list<GameEngineCollision*>::iterator ObjectStartIter = Group.begin();
			std::list<GameEngineCollision*>::iterator ObjectEndIter = Group.end();

			for (; ObjectStartIter != ObjectEndIter; )
			{
				GameEngineCollision* Object = *ObjectStartIter;
				if (false == Object->IsDeath())
				{
					++ObjectStartIter;
					continue;
				}

				ObjectStartIter = Group.erase(ObjectStartIter);

			}
		}
	}
}

void GameEngineLevel::OverCheck(GameEngineLevel* _PrevLevel)
{
	if (nullptr == _PrevLevel)
	{
		return;
	}
	// 이전레벨에 존재하는 이 액터와 관련된 랜더러와
	_PrevLevel->MainCamera->OverRelease();
	// 이전레벨에 존재하는 이 액터와 관련된 충돌체 모두 릴리즈한다.
	_PrevLevel->CollisionOverRelease();

	for (std::pair<const int, std::list<GameEngineActor*>>& _Pair : _PrevLevel->AllActors)
	{
		std::list<GameEngineActor*>& Group = _Pair.second;

		std::list<GameEngineActor*>::iterator StartIter = Group.begin();
		std::list<GameEngineActor*>::iterator EndIter = Group.end();

		for (; StartIter != EndIter;)
		{
			GameEngineActor* Actor = *StartIter;

			if (false == Actor->IsLevelOver())
			{
				++StartIter;
				continue;
			}

			Actor->Level = this;

			for (GameEngineRenderer* Render : Actor->AllRenderer)
			{
				if (Render->CameraTypeValue == CameraType::MAIN)
				{
					Render->MainCameraSetting();
				}
				else
				{
					Render->UICameraSetting();
				}

				Render->SetOrder(Render->GetOrder());
			}

			for (GameEngineCollision* Collision : Actor->AllCollision)
			{
				Collision->SetOrder(Collision->GetOrder());
			}

			AllActors[Actor->GetOrder()].push_back(Actor);

			StartIter = Group.erase(StartIter);
		}
	}
}
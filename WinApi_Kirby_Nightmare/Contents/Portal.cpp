#include "Portal.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Kirby.h"
#include "FadeObject.h"

Portal::Portal()
{

}

Portal::~Portal()
{

}

void Portal::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("KirbyIdel.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Hub World\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Portal.bmp"), 5, 10);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BlackDoor.bmp"), 1, 1);
		}
	}

	Door = CreateRenderer(RenderOrder::Stage);
	Door->SetTexture("Blank.bmp");
	SubDoor = CreateRenderer(RenderOrder::Stage);
	SubDoor->SetTexture("Blank.bmp");

	Door->CreateAnimation("CloseDoor", "Portal.bmp", 0, 0, 0.1f, false);
	Door->CreateAnimation("OpeningDoor", "Portal.bmp", 4, 6, 0.2f, false);
	Door->CreateAnimation("OpenDoor", "Portal.bmp", 6, 6, 0.2f, false);
	SubDoor->CreateAnimation("BlackDoor", "BlackDoor.bmp", 0, 0, 0.1f, false);
	Door->SetScaleRatio(4.0f);
	//Door->ChangeAnimation("CloseDoor");
	ChangeState(PortalState::Close);

	BodyCollision = CreateCollision(CollisionOrder::Portal);
	BodyCollision->SetCollisionScale(BodyCollisionScale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
}

void Portal::Update(float _Delta)
{

	std::vector<GameEngineCollision*> _Col;

	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody
		, _Col
		, CollisionType::Rect // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			if (true == GameEngineInput::IsPress('W'))
			{
				ChangeState(PortalState::Opening);
				return;
			}
		}
	}

	StateUpdate(_Delta);
}


void Portal::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	AnimationName += _StateName;

	CurState = _StateName;

	Door->ChangeAnimation(AnimationName);
}

void Portal::ChangeState(PortalState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PortalState::Close:
			CloseStart();
			break;
		case PortalState::Opening:
			OpeningStart();
			break;
		case PortalState::Open:
			OpenStart();
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}


void Portal::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PortalState::Close:
		return CloseUpdate(_Delta);
	case PortalState::Opening:
		return OpeningUpdate(_Delta);
	case PortalState::Open:
		return OpenUpdate(_Delta);
	default:
		break;
	}
}

void Portal::CloseStart()
{
	ChangeAnimationState("CloseDoor");
}

void Portal::CloseUpdate(float _Delta)
{

}

void Portal::OpeningStart()
{
	FadeObject* FObject = GetLevel()->CreateActor<FadeObject>();
	FObject->FadeOut();

	ChangeAnimationState("OpeningDoor");
}
void Portal::OpeningUpdate(float _Delta)
{
	if (0.7f < GetLiveTime())
	{
		ChangeState(PortalState::Open);
		return;
	}
}

void Portal::OpenStart()
{
	ChangeAnimationState("OpenDoor");
}

void Portal::OpenUpdate(float _Delta)
{
	if (0.2f < GetLiveTime())
	{
		ChangeState(PortalState::Close);
		GameEngineCore::ChangeLevel(CurLevel);
	}
}


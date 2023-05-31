#include "WaddleDee.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

WaddleDee::WaddleDee()
{

}

WaddleDee::~WaddleDee()
{

}

void WaddleDee::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("WaddleDeeLeft.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Enemies\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WaddleDeeLeft.bmp"), 3, 3);
		}

		{ // RinghtAnimation 셋팅
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WaddleDeeRight.bmp"), 3, 3);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);

	MainRenderer->CreateAnimation("WaddleDeeLeft_Idle", "WaddleDeeLeft.bmp", 2, 2, 0.1f, true);
	MainRenderer->CreateAnimation("WaddleDeeLeft_Walk", "WaddleDeeLeft.bmp", 1, 4, 0.3f, true);
	MainRenderer->CreateAnimation("WaddleDeeRight_Idle", "WaddleDeeRight.bmp", 2, 2, 0.1f, true);
	MainRenderer->CreateAnimation("WaddleDeeRight_Walk", "WaddleDeeRight.bmp", 1, 4, 0.3f, true);

	{ // 충돌체 설정
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionScale(CollisionScale);
		BodyCollision->SetCollisionPos(CollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);
	}

	MainRenderer->SetScaleRatio(4.0f);
	SetPos(float4{ 500,360 });
	SetGroundTexture("Level1_Debug.bmp");

	ChangeState(WaddleDeeState::Idle);
}

void WaddleDee::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _Col;
	//플레이어 몸통과 충돌.
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Death();

		}
	}
	//플레이어 공격과 충돌.
	if (true == BodyCollision->Collision(CollisionOrder::PlayerAttack
		, _Col
		, CollisionType::CirCle // 나의 충돌체 모양
		, CollisionType::CirCle // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Death();

		}
	}

	StateUpdate(_Delta);
	GroundCheck(_Delta);
}

void WaddleDee::StateUpdate(float _Delta)
{
	switch (State)
	{
	case WaddleDeeState::Idle:
		return IdleUpdate(_Delta);
	case WaddleDeeState::Walk:
		return WalkUpdate(_Delta);
	default:
		break;
	}
}

void WaddleDee::ChangeState(WaddleDeeState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case WaddleDeeState::Idle:
			IdleStart();
			break;
		case WaddleDeeState::Walk:
			WalkStart();
			break;
		default:
			break;
		}
	}
	ResetLiveTime();

	State = _State;
}


void WaddleDee::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case WaddleDeeDir::Right:
		AnimationName = "WaddleDeeRight_";
		break;
	case WaddleDeeDir::Left:
		AnimationName = "WaddleDeeLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

unsigned int WaddleDee::GetWallCheck()
{
	unsigned int WallColor = GetGroundColor(RGB(255, 255, 255), CheckPos);
	return WallColor;
}

void WaddleDee::Movement(float _Delta)
{
	if (Dir == WaddleDeeDir::Left)
	{
		CheckPos = { -40.0f, -40.0f };
		MovePos = { -Speed * _Delta, 0.0f };

		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = WaddleDeeDir::Right;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
	else if (Dir == WaddleDeeDir::Right)
	{
		CheckPos = { 40.0f, -40.0f };
		MovePos = { Speed * _Delta, 0.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = WaddleDeeDir::Left;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
}
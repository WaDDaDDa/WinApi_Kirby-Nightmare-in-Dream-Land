#include "WaddleDee.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"


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
	MainRenderer->SetTexture("Blank.bmp");
	{ // 애니메이션 설정
		MainRenderer->CreateAnimation("WaddleDeeLeft_Idle", "WaddleDeeLeft.bmp", 2, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_Walk", "WaddleDeeLeft.bmp", 1, 4, 0.3f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_HitReady", "WaddleDeeLeft.bmp", 5, 5, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_Hit", "WaddleDeeLeft.bmp", 5, 5, 0.1f, true);
		//MainRenderer->CreateAnimation("WaddleDeeLeft_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_Effect", "Effect1.bmp", 0, 6, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeLeft_Damage", "WaddleDeeLeft.bmp", 5, 5, 0.1f, true);

		MainRenderer->CreateAnimation("WaddleDeeRight_Idle", "WaddleDeeRight.bmp", 2, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_Walk", "WaddleDeeRight.bmp", 1, 4, 0.3f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_HitReady", "WaddleDeeRight.bmp", 5, 5, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_Hit", "WaddleDeeRight.bmp", 5, 5, 0.1f, true);
		//MainRenderer->CreateAnimation("WaddleDeeRight_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_Effect", "Effect1.bmp", 0, 6, 0.1f, true);
		MainRenderer->CreateAnimation("WaddleDeeRight_Damage", "WaddleDeeRight.bmp", 5, 5, 0.1f, true);
	}

	{ // 충돌체 설정
		BodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		BodyCollision->SetCollisionScale(CollisionScale);
		BodyCollision->SetCollisionPos(CollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);

		DeathCollision = CreateCollision(CollisionOrder::DeathBody);
		DeathCollision->SetCollisionScale(DeathCollisionScale);
		DeathCollision->SetCollisionPos(CollisionPos);
		DeathCollision->SetCollisionType(CollisionType::CirCle);
		DeathCollision->Off();
	}
	MainRenderer->SetScaleRatio(4.0f);

	SetOrder(UpdateOrder::Monster);
	SetAbillity(Abillity::Normal);
	ChangeState(WaddleDeeState::Idle);
}

void WaddleDee::Update(float _Delta)
{
	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(GetOrder()))
	{
		return;
	}

	StateUpdate(_Delta);
	//GroundCheck(_Delta);

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
			Actor = Collison->GetActor();
			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			ChangeState(WaddleDeeState::Damage);
			return;
		}
	}
	//플레이어 공격과 충돌.
	if (true == BodyCollision->Collision(CollisionOrder::VacumAttack
		, _Col
		, CollisionType::CirCle // 나의 충돌체 모양
		, CollisionType::Rect // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			ChangeState(WaddleDeeState::HitReady);
			return;
		}
	}
	// 공기나 별 과 충돌
	if (true == BodyCollision->Collision(CollisionOrder::PlayerAttack
		, _Col
		, CollisionType::CirCle // 나의 충돌체 모양
		, CollisionType::CirCle // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			Collison->Off();
			BodyCollision->Off();
			ChangeState(WaddleDeeState::Damage);
			return;
		}
	}
	// 버닝공격과 충돌
	if (true == BodyCollision->Collision(CollisionOrder::BurningAttack
		, _Col
		, CollisionType::CirCle // 나의 충돌체 모양
		, CollisionType::Rect // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			BodyCollision->Off();
			ChangeState(WaddleDeeState::Damage);
			return;
		}
	}
	// 전기공격과 충돌
	if (true == BodyCollision->Collision(CollisionOrder::SparkAttack
		, _Col
		, CollisionType::CirCle // 나의 충돌체 모양
		, CollisionType::CirCle // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			BodyCollision->Off();
			ChangeState(WaddleDeeState::Damage);
			return;
		}
	}

	// 검기공격과 충돌
	if (true == BodyCollision->Collision(CollisionOrder::SwordAttack
		, _Col
		, CollisionType::CirCle // 나의 충돌체 모양
		, CollisionType::CirCle // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			if (GetPos().X > ActorPos.X)
			{
				Dir = WaddleDeeDir::Left;
			}
			else
			{
				Dir = WaddleDeeDir::Right;
			}
			BodyCollision->Off();
			GameEngineSound::SoundPlay("song145.wav");
			ChangeState(WaddleDeeState::Damage);
			return;
		}
	}

}

void WaddleDee::StateUpdate(float _Delta)
{
	switch (State)
	{
	case WaddleDeeState::Idle:
		return IdleUpdate(_Delta);
	case WaddleDeeState::Walk:
		return WalkUpdate(_Delta);
	case WaddleDeeState::HitReady:
		return HitReadyUpdate(_Delta);
	case WaddleDeeState::Hit:
		return HitUpdate(_Delta);
	case WaddleDeeState::Damage:
		return DamageUpdate(_Delta);
	case WaddleDeeState::Effect:
		return EffectUpdate(_Delta);
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
		case WaddleDeeState::HitReady:
			HitReadyStart();
			break;
		case WaddleDeeState::Hit:
			HitStart();
			break;
		case WaddleDeeState::Damage:
			DamageStart();
			break;
		case WaddleDeeState::Effect:
			EffectStart();
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
	float4 MovePos1 = float4::ZERO;

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

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255))
		{
			// MovePos를 바꿔버리는 방법이 있을것이고.

			if (RGB(255, 255, 255) == GetGroundColor(RGB(255, 255, 255), MovePos1))
			{
				float4 XPos = float4::ZERO;
				float4 Dir = MovePos1.X <= 0.0f ? float4::RIGHT : float4::LEFT;

				while (RGB(0, 255, 0) != GetGroundColor(RGB(255, 255, 255), MovePos1 + XPos))
				{
					XPos += Dir;

					if (abs(XPos.X) > 50.0f)
					{
						break;
					}
				}

				float4 YPos = float4::ZERO;
				while (RGB(0, 255, 0) != GetGroundColor(RGB(255, 255, 255), MovePos1 + YPos))
				{
					YPos.Y += 1;

					if (YPos.Y > 60.0f)
					{
						break;
					}
				}

				if (abs(XPos.X) >= YPos.Y)
				{
					while (RGB(0, 255, 0) != GetGroundColor(RGB(255, 255, 255), MovePos1))
					{
						MovePos1.Y += 1;
					}
				}

			}

			AddPos(MovePos1);
		}
	}

	//if (Dir == WaddleDeeDir::Left)
	//{
	//	CheckPos = { -40.0f, -40.0f };
	//	MovePos = { -Speed * _Delta, 0.0f };

	//	// 벽판정
	//	if (GetWallCheck() != RGB(255, 255, 255))
	//	{
	//		MovePos.X *= 0;
	//		Dir = WaddleDeeDir::Right;
	//		ChangeAnimationState(CurState);
	//		return;
	//	}
	//	AddPos(MovePos);
	//}
	//else if (Dir == WaddleDeeDir::Right)
	//{
	//	CheckPos = { 40.0f, -40.0f };
	//	MovePos = { Speed * _Delta, 0.0f };

	//	if (GetWallCheck() != RGB(255, 255, 255))
	//	{
	//		MovePos.X *= 0;
	//		Dir = WaddleDeeDir::Left;
	//		ChangeAnimationState(CurState);
	//		return;
	//	}
	//	AddPos(MovePos);
	//}
}
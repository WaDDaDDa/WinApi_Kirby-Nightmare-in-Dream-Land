#include "WheelMonster.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"


WheelMonster::WheelMonster()
{

}

WheelMonster::~WheelMonster()
{

}

void WheelMonster::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("WheelMonsterLeft.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Enemies\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WheelMonsterLeft.bmp"), 5, 2);
		}

		{ // RinghtAnimation 셋팅
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WheelMonsterRight.bmp"), 5, 2);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetTexture("Blank.bmp");
	{ // 애니메이션 설정
		MainRenderer->CreateAnimation("WheelMonsterLeft_Idle", "WheelMonsterLeft.bmp", 1, 1, 0.1f, false);
		MainRenderer->CreateAnimation("WheelMonsterLeft_Walk", "WheelMonsterLeft.bmp", 0, 0, 0.3f, false);
		MainRenderer->CreateAnimation("WheelMonsterLeft_HitReady", "WheelMonsterLeft.bmp", 5, 5, 0.1f, false);
		MainRenderer->CreateAnimation("WheelMonsterLeft_Hit", "WheelMonsterLeft.bmp", 5, 5, 0.1f, false);
		//MainRenderer->CreateAnimation("WheelMonsterLeft_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WheelMonsterLeft_Effect", "Effect1.bmp", 0, 6, 0.1f, true);
		MainRenderer->CreateAnimation("WheelMonsterLeft_Damage", "WheelMonsterLeft.bmp", 5, 5, 0.1f, false);

		MainRenderer->CreateAnimation("WheelMonsterRight_Idle", "WheelMonsterRight.bmp", 1, 1, 0.1f, false);
		MainRenderer->CreateAnimation("WheelMonsterRight_Walk", "WheelMonsterRight.bmp", 0, 0, 0.3f, false);
		MainRenderer->CreateAnimation("WheelMonsterRight_HitReady", "WheelMonsterRight.bmp", 5, 5, 0.1f, false);
		MainRenderer->CreateAnimation("WheelMonsterRight_Hit", "WheelMonsterRight.bmp", 5, 5, 0.1f, false);
		//MainRenderer->CreateAnimation("WheelMonsterRight_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("WheelMonsterRight_Effect", "Effect1.bmp", 0, 6, 0.1f, true);
		MainRenderer->CreateAnimation("WheelMonsterRight_Damage", "WheelMonsterRight.bmp", 5, 5, 0.1f, false);
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
	SetAbillity(Abillity::Wheel);
	ChangeState(WheelMonsterState::Idle);
}

void WheelMonster::Update(float _Delta)
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
				Dir = WheelMonsterDir::Left;
			}
			else
			{
				Dir = WheelMonsterDir::Right;
			}
			GameEngineSound::SoundPlay("42 부딪히는소리.wav");
			ChangeState(WheelMonsterState::Damage);
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
				Dir = WheelMonsterDir::Left;
			}
			else
			{
				Dir = WheelMonsterDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			ChangeState(WheelMonsterState::HitReady);
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
				Dir = WheelMonsterDir::Left;
			}
			else
			{
				Dir = WheelMonsterDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			Collison->Off();
			BodyCollision->Off();
			GameEngineSound::SoundPlay("42 부딪히는소리.wav");
			ChangeState(WheelMonsterState::Damage);
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
				Dir = WheelMonsterDir::Left;
			}
			else
			{
				Dir = WheelMonsterDir::Right;
			}
			BodyCollision->Off();
			GameEngineSound::SoundPlay("42 부딪히는소리.wav");
			ChangeState(WheelMonsterState::Damage);
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
				Dir = WheelMonsterDir::Left;
			}
			else
			{
				Dir = WheelMonsterDir::Right;
			}
			BodyCollision->Off();
			GameEngineSound::SoundPlay("42 부딪히는소리.wav");
			ChangeState(WheelMonsterState::Damage);
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
				Dir = WheelMonsterDir::Left;
			}
			else
			{
				Dir = WheelMonsterDir::Right;
			}
			BodyCollision->Off();
			GameEngineSound::SoundPlay("song145.wav");
			ChangeState(WheelMonsterState::Damage);
			return;
		}
	}

}

void WheelMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case WheelMonsterState::Idle:
		return IdleUpdate(_Delta);
	case WheelMonsterState::Walk:
		return WalkUpdate(_Delta);
	case WheelMonsterState::HitReady:
		return HitReadyUpdate(_Delta);
	case WheelMonsterState::Hit:
		return HitUpdate(_Delta);
	case WheelMonsterState::Damage:
		return DamageUpdate(_Delta);
	case WheelMonsterState::Effect:
		return EffectUpdate(_Delta);
	default:
		break;
	}
}

void WheelMonster::ChangeState(WheelMonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case WheelMonsterState::Idle:
			IdleStart();
			break;
		case WheelMonsterState::Walk:
			WalkStart();
			break;
		case WheelMonsterState::HitReady:
			HitReadyStart();
			break;
		case WheelMonsterState::Hit:
			HitStart();
			break;
		case WheelMonsterState::Damage:
			DamageStart();
			break;
		case WheelMonsterState::Effect:
			EffectStart();
			break;
		default:
			break;
		}
	}
	ResetLiveTime();

	State = _State;
}


void WheelMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case WheelMonsterDir::Right:
		AnimationName = "WheelMonsterRight_";
		break;
	case WheelMonsterDir::Left:
		AnimationName = "WheelMonsterLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

unsigned int WheelMonster::GetWallCheck()
{
	unsigned int WallColor = GetGroundColor(RGB(255, 255, 255), CheckPos);
	return WallColor;
}

void WheelMonster::Movement(float _Delta)
{
	float4 MovePos1 = float4::ZERO;

	if (Dir == WheelMonsterDir::Left)
	{
		CheckPos = { -40.0f, -40.0f };
		MovePos = { -Speed * _Delta, 0.0f };
		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = WheelMonsterDir::Right;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
	else if (Dir == WheelMonsterDir::Right)
	{
		CheckPos = { 40.0f, -40.0f };
		MovePos = { Speed * _Delta, 0.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = WheelMonsterDir::Left;
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

	//if (Dir == WheelMonsterDir::Left)
	//{
	//	CheckPos = { -40.0f, -40.0f };
	//	MovePos = { -Speed * _Delta, 0.0f };

	//	// 벽판정
	//	if (GetWallCheck() != RGB(255, 255, 255))
	//	{
	//		MovePos.X *= 0;
	//		Dir = WheelMonsterDir::Right;
	//		ChangeAnimationState(CurState);
	//		return;
	//	}
	//	AddPos(MovePos);
	//}
	//else if (Dir == WheelMonsterDir::Right)
	//{
	//	CheckPos = { 40.0f, -40.0f };
	//	MovePos = { Speed * _Delta, 0.0f };

	//	if (GetWallCheck() != RGB(255, 255, 255))
	//	{
	//		MovePos.X *= 0;
	//		Dir = WheelMonsterDir::Left;
	//		ChangeAnimationState(CurState);
	//		return;
	//	}
	//	AddPos(MovePos);
	//}
}
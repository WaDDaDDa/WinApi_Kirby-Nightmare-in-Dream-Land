#include "SparkMonster.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

SparkMonster::SparkMonster()
{

}

SparkMonster::~SparkMonster()
{

}

void SparkMonster::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("SparkMonsterLeft.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Enemies\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SparkMonsterLeft.bmp"), 7, 3);
		}

		{ // RinghtAnimation 셋팅
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SparkMonsterRight.bmp"), 7, 3);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetTexture("Blank.bmp");
	AttRenderer = CreateRenderer(RenderOrder::BackEffect);
	AttRenderer->SetTexture("Blank.bmp");

	{ // 애니메이션 설정
		MainRenderer->CreateAnimation("SparkMonsterLeft_Idle", "SparkMonsterLeft.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Walk", "SparkMonsterLeft.bmp", 1, 5, 0.3f, true);
		MainRenderer->CreateAnimation("SparkMonsterLeft_HitReady", "SparkMonsterLeft.bmp", 4, 4, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Hit", "SparkMonsterLeft.bmp", 4, 4, 0.1f, false);
		//MainRenderer->CreateAnimation("SparkMonsterLeft_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Effect", "Effect1.bmp", 0, 6, 0.1f, true);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Damage", "SparkMonsterLeft.bmp", 4, 4, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterLeft_AttackStart", "SparkMonsterLeft.bmp", 6, 6, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Attack", "SparkMonsterLeft.bmp", 7, 8, 0.1f, true);

		MainRenderer->CreateAnimation("SparkMonsterRight_Idle", "SparkMonsterRight.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_Walk", "SparkMonsterRight.bmp", 1, 5, 0.3f, true);
		MainRenderer->CreateAnimation("SparkMonsterRight_HitReady", "SparkMonsterRight.bmp", 4, 4, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_Hit", "SparkMonsterRight.bmp", 4, 4, 0.1f, false);
		//MainRenderer->CreateAnimation("SparkMonsterRight_Effect", "DamageEffects.bmp", 0, 2, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_Effect", "Effect1.bmp", 0, 6, 0.1f, true);
		MainRenderer->CreateAnimation("SparkMonsterRight_Damage", "SparkMonsterRight.bmp", 4, 4, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_AttackStart", "SparkMonsterRight.bmp", 6, 6, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_Attack", "SparkMonsterRight.bmp", 7, 8, 0.1f, true);
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

		AttackCollision = CreateCollision(CollisionOrder::MonsterSparkAttack);
		AttackCollision->SetCollisionScale(AttackCollisionScale);
		AttackCollision->SetCollisionPos(AttackCollisionPos);
		AttackCollision->SetCollisionType(CollisionType::CirCle);
		AttackCollision->Off();
	}


	AttRenderer->CreateAnimation("SparkEffect", "SparkEffect.bmp", 0, 3, 0.1f, true);
	AttRenderer->ChangeAnimation("SparkEffect");
	AttRenderer->SetRenderPos(AttackCollisionPos);
	AttRenderer->SetScaleRatio(3.5f);
	AttRenderer->Off();

	MainRenderer->SetScaleRatio(4.0f);

	SetOrder(UpdateOrder::Monster);
	SetAbillity(Abillity::Spark);
	ChangeState(SparkMonsterState::Idle);
}

void SparkMonster::Update(float _Delta)
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
				Dir = SparkMonsterDir::Left;
			}
			else
			{
				Dir = SparkMonsterDir::Right;
			}
			GameEngineSound::SoundPlay("42 부딪히는소리.wav");
			ChangeState(SparkMonsterState::Damage);
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
				Dir = SparkMonsterDir::Left;
			}
			else
			{
				Dir = SparkMonsterDir::Right;
			}
			AttRenderer->Off();
			ChangeState(SparkMonsterState::HitReady);
			return;
		}
	}

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
				Dir = SparkMonsterDir::Left;
			}
			else
			{
				Dir = SparkMonsterDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			Collison->Off();
			BodyCollision->Off();
			GameEngineSound::SoundPlay("42 부딪히는소리.wav");
			ChangeState(SparkMonsterState::Damage);
			return;
		}
	}

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
				Dir = SparkMonsterDir::Left;
			}
			else
			{
				Dir = SparkMonsterDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			BodyCollision->Off();
			AttRenderer->Off();
			AttackCollision->Off();
			GameEngineSound::SoundPlay("42 부딪히는소리.wav");
			ChangeState(SparkMonsterState::Damage);
			return;
		}
	}

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
				Dir = SparkMonsterDir::Left;
			}
			else
			{
				Dir = SparkMonsterDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			BodyCollision->Off();
			AttRenderer->Off();
			AttackCollision->Off();
			GameEngineSound::SoundPlay("42 부딪히는소리.wav");
			ChangeState(SparkMonsterState::Damage);
			return;
		}
	}

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
				Dir = SparkMonsterDir::Left;
			}
			else
			{
				Dir = SparkMonsterDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			BodyCollision->Off();
			AttRenderer->Off();
			AttackCollision->Off();
			GameEngineSound::SoundPlay("song145.wav");
			ChangeState(SparkMonsterState::Damage);
			return;
		}
	}
}

void SparkMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SparkMonsterState::Idle:
		return IdleUpdate(_Delta);
	case SparkMonsterState::Walk:
		return WalkUpdate(_Delta);
	case SparkMonsterState::HitReady:
		return HitReadyUpdate(_Delta);
	case SparkMonsterState::Hit:
		return HitUpdate(_Delta);
	case SparkMonsterState::Damage:
		return DamageUpdate(_Delta);
	case SparkMonsterState::Effect:
		return EffectUpdate(_Delta);
	case SparkMonsterState::AttackStart:
		return AttackStartUpdate(_Delta);
	case SparkMonsterState::Attack:
		return AttackUpdate(_Delta);
	default:
		break;
	}
}

void SparkMonster::ChangeState(SparkMonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case SparkMonsterState::Idle:
			IdleStart();
			break;
		case SparkMonsterState::Walk:
			WalkStart();
			break;
		case SparkMonsterState::HitReady:
			HitReadyStart();
			break;
		case SparkMonsterState::Hit:
			HitStart();
			break;
		case SparkMonsterState::Damage:
			DamageStart();
			break;
		case SparkMonsterState::Effect:
			EffectStart();
			break;
		case SparkMonsterState::AttackStart:
			AttackStartStart();
			break;
		case SparkMonsterState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}
	ResetLiveTime();

	State = _State;
}


void SparkMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case SparkMonsterDir::Right:
		AnimationName = "SparkMonsterRight_";
		break;
	case SparkMonsterDir::Left:
		AnimationName = "SparkMonsterLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

unsigned int SparkMonster::GetWallCheck()
{
	unsigned int WallColor = GetGroundColor(RGB(255, 255, 255), CheckPos);
	return WallColor;
}

void SparkMonster::Movement(float _Delta)
{
	if (Dir == SparkMonsterDir::Left)
	{
		CheckPos = { -40.0f, -40.0f };
		MovePos = { -Speed * _Delta, 0.0f };

		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = SparkMonsterDir::Right;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
	else if (Dir == SparkMonsterDir::Right)
	{
		CheckPos = { 40.0f, -40.0f };
		MovePos = { Speed * _Delta, 0.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = SparkMonsterDir::Left;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
}
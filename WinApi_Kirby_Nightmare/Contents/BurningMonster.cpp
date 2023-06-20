#include "BurningMonster.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

BurningMonster::BurningMonster()
{

}

BurningMonster::~BurningMonster()
{

}

void BurningMonster::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("BurningMonsterLeft.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Enemies\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BurningMonsterLeft.bmp"), 5, 2);
		}

		{ // RinghtAnimation 셋팅
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BurningMonsterRight.bmp"), 5, 2);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	LeftAttackRenderer = CreateRenderer(RenderOrder::Effect);
	LeftAttack2Renderer = CreateRenderer(RenderOrder::Effect2);
	RightAttackRenderer = CreateRenderer(RenderOrder::Effect);
	RightAttack2Renderer = CreateRenderer(RenderOrder::Effect2);

	{ // 애니메이션 설정
		MainRenderer->CreateAnimation("BurningMonsterLeft_Idle", "BurningMonsterLeft.bmp", 3, 3, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterLeft_Walk", "BurningMonsterLeft.bmp", 1, 5, 0.3f, true);
		MainRenderer->CreateAnimation("BurningMonsterLeft_HitReady", "BurningMonsterLeft.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterLeft_Hit", "BurningMonsterLeft.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterLeft_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("BurningMonsterLeft_Damage", "BurningMonsterLeft.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterLeft_AttackStart", "BurningMonsterLeft.bmp", 6, 6, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterLeft_Attack1", "BurningMonsterLeft.bmp", 7, 8, 0.1f, true);
		MainRenderer->CreateAnimation("BurningMonsterLeft_Attack2", "BurningMonsterLeft.bmp", 7, 9, 0.1f, false);

		MainRenderer->CreateAnimation("BurningMonsterRight_Idle", "BurningMonsterRight.bmp", 3, 3, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterRight_Walk", "BurningMonsterRight.bmp", 1, 5, 0.3f, true);
		MainRenderer->CreateAnimation("BurningMonsterRight_HitReady", "BurningMonsterRight.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterRight_Hit", "BurningMonsterRight.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterRight_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("BurningMonsterRight_Damage", "BurningMonsterRight.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterRight_AttackStart", "BurningMonsterRight.bmp", 6, 6, 0.1f, false);
		MainRenderer->CreateAnimation("BurningMonsterRight_Attack1", "BurningMonsterRight.bmp", 7, 8, 0.1f, true);
		MainRenderer->CreateAnimation("BurningMonsterRight_Attack2", "BurningMonsterRight.bmp", 7, 9, 0.1f, false);
	}

	{
		LeftAttackRenderer->CreateAnimation("FireAttackLeft", "FireEffect1Left.bmp", 0, 6, 0.1f, true);
		LeftAttack2Renderer->CreateAnimation("FireAttack2Left", "FireEffect2Left.bmp", 0, 6, 0.1f, true);

		RightAttackRenderer->CreateAnimation("FireAttackRight", "FireEffect1Right.bmp", 0, 6, 0.1f, true);
		RightAttack2Renderer->CreateAnimation("FireAttack2Right", "FireEffect2Right.bmp", 0, 6, 0.1f, true);
	}

	LeftAttackRenderer->ChangeAnimation("FireAttackLeft");
	LeftAttack2Renderer->ChangeAnimation("FireAttack2Left");

	RightAttackRenderer->ChangeAnimation("FireAttackRight");
	RightAttack2Renderer->ChangeAnimation("FireAttack2Right");

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

		AttackCollision = CreateCollision(CollisionOrder::MonsterFireAttack);
		AttackCollision->SetCollisionScale(AttackCollisionScale);
		AttackCollision->SetCollisionPos(AttackCollisionPos);
		AttackCollision->SetCollisionType(CollisionType::Rect);
		AttackCollision->Off();
	}
	MainRenderer->SetScaleRatio(4.0f);

	RightAttackRenderer->SetRenderPos({ 100, -40 });
	RightAttack2Renderer->SetRenderPos({ 100, -40 });

	LeftAttackRenderer->SetRenderPos({ -100, -40 });
	LeftAttack2Renderer->SetRenderPos({ -100, -40 });

	LeftAttackRenderer->SetScaleRatio(3.0f);
	LeftAttack2Renderer->SetScaleRatio(3.0f);
	RightAttackRenderer->SetScaleRatio(3.0f);
	RightAttack2Renderer->SetScaleRatio(3.0f);
	LeftAttackRenderer->Off();
	LeftAttack2Renderer->Off();
	RightAttackRenderer->Off();
	RightAttack2Renderer->Off();

	SetOrder(UpdateOrder::Monster);

	SetAbillity(Abillity::Burning);
	ChangeState(BurningMonsterState::Idle);
}

void BurningMonster::Update(float _Delta)
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
				Dir = BurningMonsterDir::Left;
			}
			else
			{
				Dir = BurningMonsterDir::Right;
			}
			LeftAttackRenderer->Off();
			LeftAttack2Renderer->Off();
			RightAttackRenderer->Off();
			RightAttack2Renderer->Off();
			ChangeState(BurningMonsterState::Damage);
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
				Dir = BurningMonsterDir::Left;
			}
			else
			{
				Dir = BurningMonsterDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			LeftAttackRenderer->Off();
			LeftAttack2Renderer->Off();
			RightAttackRenderer->Off();
			RightAttack2Renderer->Off();
			ChangeState(BurningMonsterState::HitReady);
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
				Dir = BurningMonsterDir::Left;
			}
			else
			{
				Dir = BurningMonsterDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			Collison->Off();
			BodyCollision->Off();
			LeftAttackRenderer->Off();
			LeftAttack2Renderer->Off();
			RightAttackRenderer->Off();
			RightAttack2Renderer->Off();
			ChangeState(BurningMonsterState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::SpecialAttack
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
				Dir = BurningMonsterDir::Left;
			}
			else
			{
				Dir = BurningMonsterDir::Right;
			}
			// 계속 흡수당하고있음.
			// 흡수당하는건 한번만 해야함.
			BodyCollision->Off();
			LeftAttackRenderer->Off();
			LeftAttack2Renderer->Off();
			RightAttackRenderer->Off();
			RightAttack2Renderer->Off();
			ChangeState(BurningMonsterState::Damage);
			return;
		}
	}
}

void BurningMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BurningMonsterState::Idle:
		return IdleUpdate(_Delta);
	case BurningMonsterState::Walk:
		return WalkUpdate(_Delta);
	case BurningMonsterState::HitReady:
		return HitReadyUpdate(_Delta);
	case BurningMonsterState::Hit:
		return HitUpdate(_Delta);
	case BurningMonsterState::Damage:
		return DamageUpdate(_Delta);
	case BurningMonsterState::Effect:
		return EffectUpdate(_Delta);
	case BurningMonsterState::AttackStart:
		return AttackStartUpdate(_Delta);
	case BurningMonsterState::Attack1:
		return Attack1Update(_Delta);
	case BurningMonsterState::Attack2:
		return Attack2Update(_Delta);
	default:
		break;
	}
}

void BurningMonster::ChangeState(BurningMonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BurningMonsterState::Idle:
			IdleStart();
			break;
		case BurningMonsterState::Walk:
			WalkStart();
			break;
		case BurningMonsterState::HitReady:
			HitReadyStart();
			break;
		case BurningMonsterState::Hit:
			HitStart();
			break;
		case BurningMonsterState::Damage:
			DamageStart();
			break;
		case BurningMonsterState::Effect:
			EffectStart();
			break;
		case BurningMonsterState::AttackStart:
			AttackStartStart();
			break;
		case BurningMonsterState::Attack1:
			Attack1Start();
			break;
		case BurningMonsterState::Attack2:
			Attack2Start();
			break;
		default:
			break;
		}
	}
	ResetLiveTime();

	State = _State;
}


void BurningMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case BurningMonsterDir::Right:
		AnimationName = "BurningMonsterRight_";
		break;
	case BurningMonsterDir::Left:
		AnimationName = "BurningMonsterLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

unsigned int BurningMonster::GetWallCheck()
{
	unsigned int WallColor = GetGroundColor(RGB(255, 255, 255), CheckPos);
	return WallColor;
}

void BurningMonster::Movement(float _Delta)
{
	if (Dir == BurningMonsterDir::Left)
	{
		CheckPos = { -40.0f, -40.0f };
		MovePos = { -Speed * _Delta, 0.0f };

		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = BurningMonsterDir::Right;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
	else if (Dir == BurningMonsterDir::Right)
	{
		CheckPos = { 40.0f, -40.0f };
		MovePos = { Speed * _Delta, 0.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = BurningMonsterDir::Left;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
}
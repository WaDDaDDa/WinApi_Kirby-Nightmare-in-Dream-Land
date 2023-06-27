#include "BossMonster.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"


BossMonster::BossMonster()
{

}

BossMonster::~BossMonster()
{

}

void BossMonster::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("BossMonsterLeft.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ 
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Boss\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Whispy Woods.bmp"), 5, 4);
		}

	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetTexture("Blank.Bmp");
	{ // 애니메이션 설정
		MainRenderer->CreateAnimation("BossMonster_Idle", "Whispy Woods.bmp", 3, 3, 0.1f, false);
		MainRenderer->CreateAnimation("BossMonster_Damage", "Whispy Woods.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("BossMonster_AttackStay", "Whispy Woods.bmp", 11, 13, 0.1f, false);
		MainRenderer->CreateAnimation("BossMonster_Attack", "Whispy Woods.bmp", 11, 13, 0.1f, false);
		MainRenderer->CreateAnimation("BossMonster_Over", "Whispy Woods.bmp", 6, 10, 0.5f, false);
		MainRenderer->CreateAnimation("BossMonster_SpornApple", "Whispy Woods.bmp", 14, 14, 0.5f, false);
	}

	{ // 충돌체 설정
		BodyCollision = CreateCollision(CollisionOrder::BossMonsterBody);
		BodyCollision->SetCollisionScale(BodyCollisionScale);
		BodyCollision->SetCollisionPos(BodyCollisionPos);
		BodyCollision->SetCollisionType(CollisionType::Rect);
	}
	MainRenderer->SetScaleRatio(4.0f);

	SetOrder(UpdateOrder::Monster);
	ChangeState(BossMonsterState::Idle);
}

void BossMonster::Update(float _Delta)
{
	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(GetOrder()))
	{
		return;
	}

	AttCoolTime -= _Delta;
	SpornAppleCoolTime -= _Delta;

	std::vector<GameEngineCollision*> _Col;

	if (true == BodyCollision->Collision(CollisionOrder::BossAttack
		, _Col
		, CollisionType::Rect // 나의 충돌체 모양
		, CollisionType::CirCle // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			Collison->Off();

			BossHp -= 20;

			ChangeState(BossMonsterState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::BurningAttack
		, _Col
		, CollisionType::Rect // 나의 충돌체 모양
		, CollisionType::Rect // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			Collison->Off();

			BossHp -= 5;

			ChangeState(BossMonsterState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::SparkAttack
		, _Col
		, CollisionType::Rect // 나의 충돌체 모양
		, CollisionType::Rect // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			Collison->Off();

			BossHp -= 4;

			ChangeState(BossMonsterState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::SwordAttack
		, _Col
		, CollisionType::Rect // 나의 충돌체 모양
		, CollisionType::Rect // 상대의 충돌체 모양
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Actor = Collison->GetActor();

			float4 ActorPos = Actor->GetPos();

			Collison->Off();

			BossHp -= 5;

			ChangeState(BossMonsterState::Damage);
			return;
		}
	}

	StateUpdate(_Delta);
}

void BossMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BossMonsterState::Idle:
		return IdleUpdate(_Delta);
	case BossMonsterState::AttackStay:
		return AttackStayUpdate(_Delta);
	case BossMonsterState::Attack:
		return AttackUpdate(_Delta);
	case BossMonsterState::Damage:
		return DamageUpdate(_Delta);
	case BossMonsterState::SpornApple:
		return SpornAppleUpdate(_Delta);
	default:
		break;
	}
}

void BossMonster::ChangeState(BossMonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BossMonsterState::Idle:
			IdleStart();
			break;
		case BossMonsterState::AttackStay:
			AttackStayStart();
			break;
		case BossMonsterState::Attack:
			AttackStart();
			break;
		case BossMonsterState::Damage:
			DamageStart();
			break;
		case BossMonsterState::SpornApple:
			SpornAppleStart();
			break;
		default:
			break;
		}
	}
	ResetLiveTime();

	State = _State;
}


void BossMonster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

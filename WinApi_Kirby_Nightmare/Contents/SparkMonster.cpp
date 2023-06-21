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
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation ����
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Enemies\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SparkMonsterLeft.bmp"), 7, 3);
		}

		{ // RinghtAnimation ����
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SparkMonsterRight.bmp"), 7, 3);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	LeftAttackRenderer = CreateRenderer(RenderOrder::Effect);
	LeftAttack2Renderer = CreateRenderer(RenderOrder::Effect2);
	RightAttackRenderer = CreateRenderer(RenderOrder::Effect);
	RightAttack2Renderer = CreateRenderer(RenderOrder::Effect2);

	{ // �ִϸ��̼� ����
		MainRenderer->CreateAnimation("SparkMonsterLeft_Idle", "SparkMonsterLeft.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Walk", "SparkMonsterLeft.bmp", 1, 5, 0.3f, true);
		MainRenderer->CreateAnimation("SparkMonsterLeft_HitReady", "SparkMonsterLeft.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Hit", "SparkMonsterLeft.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Damage", "SparkMonsterLeft.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterLeft_AttackStart", "SparkMonsterLeft.bmp", 6, 6, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Attack1", "SparkMonsterLeft.bmp", 7, 8, 0.1f, true);
		MainRenderer->CreateAnimation("SparkMonsterLeft_Attack2", "SparkMonsterLeft.bmp", 7, 9, 0.1f, false);

		MainRenderer->CreateAnimation("SparkMonsterRight_Idle", "SparkMonsterRight.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_Walk", "SparkMonsterRight.bmp", 1, 5, 0.3f, true);
		MainRenderer->CreateAnimation("SparkMonsterRight_HitReady", "SparkMonsterRight.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_Hit", "SparkMonsterRight.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("SparkMonsterRight_Damage", "SparkMonsterRight.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_AttackStart", "SparkMonsterRight.bmp", 6, 6, 0.1f, false);
		MainRenderer->CreateAnimation("SparkMonsterRight_Attack1", "SparkMonsterRight.bmp", 7, 8, 0.1f, true);
		MainRenderer->CreateAnimation("SparkMonsterRight_Attack2", "SparkMonsterRight.bmp", 7, 9, 0.1f, false);
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

	{ // �浹ü ����
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
	//�÷��̾� ����� �浹.
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody
		, _Col
		, CollisionType::CirCle // ���� �簢������ ����
		, CollisionType::CirCle // ��뵵 �簢������ ����
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
			LeftAttackRenderer->Off();
			LeftAttack2Renderer->Off();
			RightAttackRenderer->Off();
			RightAttack2Renderer->Off();
			ChangeState(SparkMonsterState::Damage);
			return;
		}
	}
	//�÷��̾� ���ݰ� �浹.
	if (true == BodyCollision->Collision(CollisionOrder::VacumAttack
		, _Col
		, CollisionType::CirCle // ���� �浹ü ���
		, CollisionType::Rect // ����� �浹ü ���
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
			// ��� �������ϰ�����.
			// �������ϴ°� �ѹ��� �ؾ���.
			LeftAttackRenderer->Off();
			LeftAttack2Renderer->Off();
			RightAttackRenderer->Off();
			RightAttack2Renderer->Off();
			ChangeState(SparkMonsterState::HitReady);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::PlayerAttack
		, _Col
		, CollisionType::CirCle // ���� �浹ü ���
		, CollisionType::CirCle // ����� �浹ü ���
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
			// ��� �������ϰ�����.
			// �������ϴ°� �ѹ��� �ؾ���.
			Collison->Off();
			BodyCollision->Off();
			LeftAttackRenderer->Off();
			LeftAttack2Renderer->Off();
			RightAttackRenderer->Off();
			RightAttack2Renderer->Off();
			ChangeState(SparkMonsterState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::SpecialAttack
		, _Col
		, CollisionType::CirCle // ���� �浹ü ���
		, CollisionType::Rect // ����� �浹ü ���
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
			// ��� �������ϰ�����.
			// �������ϴ°� �ѹ��� �ؾ���.
			BodyCollision->Off();
			LeftAttackRenderer->Off();
			LeftAttack2Renderer->Off();
			RightAttackRenderer->Off();
			RightAttack2Renderer->Off();
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
	case SparkMonsterState::Attack1:
		return Attack1Update(_Delta);
	case SparkMonsterState::Attack2:
		return Attack2Update(_Delta);
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
		case SparkMonsterState::Attack1:
			Attack1Start();
			break;
		case SparkMonsterState::Attack2:
			Attack2Start();
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

		// ������
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
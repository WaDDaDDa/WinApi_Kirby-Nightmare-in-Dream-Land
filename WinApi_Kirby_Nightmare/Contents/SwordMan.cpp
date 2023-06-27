#include "SwordMan.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

SwordMan::SwordMan()
{

}

SwordMan::~SwordMan()
{

}

void SwordMan::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("SwordManLeft.bmp");
	if (false == IsResource)
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation ����
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Enemies\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SwordManLeft.bmp"), 5, 4);
		}

		{ // RinghtAnimation ����
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SwordManRight.bmp"), 5, 4);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetTexture("Blank.bmp");

	{ // �ִϸ��̼� ����
		MainRenderer->CreateAnimation("SwordManLeft_Idle", "SwordManLeft.bmp", 3, 3, 0.1f, false);
		MainRenderer->CreateAnimation("SwordManLeft_Walk", "SwordManLeft.bmp", 1, 4, 0.3f, true);
		MainRenderer->CreateAnimation("SwordManLeft_HitReady", "SwordManLeft.bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("SwordManLeft_Hit", "SwordManLeft.bmp", 14, 14, 0.1f, false);
		//MainRenderer->CreateAnimation("SwordManLeft_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("SwordManLeft_Effect", "Effect1.bmp", 0, 6, 0.1f, true);
		MainRenderer->CreateAnimation("SwordManLeft_Damage", "SwordManLeft.bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("SwordManLeft_AttackStart", "SwordManLeft.bmp", 5, 5, 0.1f, false);
		MainRenderer->CreateAnimation("SwordManLeft_Attack", "SwordManLeft.bmp", 6, 11, 0.05f, false);

		MainRenderer->CreateAnimation("SwordManRight_Idle", "SwordManRight.bmp", 3, 3, 0.1f, false);
		MainRenderer->CreateAnimation("SwordManRight_Walk", "SwordManRight.bmp", 1, 4, 0.3f, true);
		MainRenderer->CreateAnimation("SwordManRight_HitReady", "SwordManRight.bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("SwordManRight_Hit", "SwordManRight.bmp", 14, 14, 0.1f, false);
		//MainRenderer->CreateAnimation("SwordManRight_Effect", "DamageEffects.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("SwordManRight_Effect", "Effect1.bmp", 0, 6, 0.1f, true);
		MainRenderer->CreateAnimation("SwordManRight_Damage", "SwordManRight.bmp", 14, 14, 0.1f, false);
		MainRenderer->CreateAnimation("SwordManRight_AttackStart", "SwordManRight.bmp", 5, 5, 0.1f, false);
		MainRenderer->CreateAnimation("SwordManRight_Attack", "SwordManRight.bmp", 6, 11, 0.05f, false);
	}


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

		RightAttackCollision = CreateCollision(CollisionOrder::MonsterSwordAttack);
		RightAttackCollision->SetCollisionScale(RightAttackCollisionScale);
		RightAttackCollision->SetCollisionPos(RightAttackCollisionPos);
		RightAttackCollision->SetCollisionType(CollisionType::Rect);
		RightAttackCollision->Off();

		LeftAttackCollision = CreateCollision(CollisionOrder::MonsterSwordAttack);
		LeftAttackCollision->SetCollisionScale(LeftAttackCollisionScale);
		LeftAttackCollision->SetCollisionPos(LeftAttackCollisionPos);
		LeftAttackCollision->SetCollisionType(CollisionType::Rect);
		LeftAttackCollision->Off();
	}
	MainRenderer->SetScaleRatio(4.0f);

	SetOrder(UpdateOrder::Monster);

	SetAbillity(Abillity::Sword);
	ChangeState(SwordManState::Idle);
}

void SwordMan::Update(float _Delta)
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
				Dir = SwordManDir::Left;
			}
			else
			{
				Dir = SwordManDir::Right;
			}
			ChangeState(SwordManState::Damage);
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
				Dir = SwordManDir::Left;
			}
			else
			{
				Dir = SwordManDir::Right;
			}
			// ��� ������ϰ�����.
			// ������ϴ°� �ѹ��� �ؾ���.
			// ������ϴ� ����
			ChangeState(SwordManState::HitReady);
			return;
		}
	}
	// ���⳪ �� ��� ���ݰ� �浹
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
				Dir = SwordManDir::Left;
			}
			else
			{
				Dir = SwordManDir::Right;
			}
			// ��� ������ϰ�����.
			// ������ϴ°� �ѹ��� �ؾ���.
			Collison->Off();
			BodyCollision->Off();
			ChangeState(SwordManState::Damage);
			return;
		}
	}
	// ���� ���ݰ� �浹
	if (true == BodyCollision->Collision(CollisionOrder::BurningAttack
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
				Dir = SwordManDir::Left;
			}
			else
			{
				Dir = SwordManDir::Right;
			}
			// ��� ������ϰ�����.
			// ������ϴ°� �ѹ��� �ؾ���.
			BodyCollision->Off();
			ChangeState(SwordManState::Damage);
			return;
		}
	}
	// ������ݰ� �浹
	if (true == BodyCollision->Collision(CollisionOrder::SparkAttack
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
				Dir = SwordManDir::Left;
			}
			else
			{
				Dir = SwordManDir::Right;
			}
			// ��� ������ϰ�����.
			// ������ϴ°� �ѹ��� �ؾ���.
			BodyCollision->Off();
			ChangeState(SwordManState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::SwordAttack
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
				Dir = SwordManDir::Left;
			}
			else
			{
				Dir = SwordManDir::Right;
			}
			// ��� ������ϰ�����.
			// ������ϴ°� �ѹ��� �ؾ���.
			BodyCollision->Off();
			ChangeState(SwordManState::Damage);
			return;
		}
	}
}

void SwordMan::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SwordManState::Idle:
		return IdleUpdate(_Delta);
	case SwordManState::Walk:
		return WalkUpdate(_Delta);
	case SwordManState::HitReady:
		return HitReadyUpdate(_Delta);
	case SwordManState::Hit:
		return HitUpdate(_Delta);
	case SwordManState::Damage:
		return DamageUpdate(_Delta);
	case SwordManState::Effect:
		return EffectUpdate(_Delta);
	case SwordManState::AttackStart:
		return AttackStartUpdate(_Delta);
	case SwordManState::Attack:
		return AttackUpdate(_Delta);
	default:
		break;
	}
}

void SwordMan::ChangeState(SwordManState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case SwordManState::Idle:
			IdleStart();
			break;
		case SwordManState::Walk:
			WalkStart();
			break;
		case SwordManState::HitReady:
			HitReadyStart();
			break;
		case SwordManState::Hit:
			HitStart();
			break;
		case SwordManState::Damage:
			DamageStart();
			break;
		case SwordManState::Effect:
			EffectStart();
			break;
		case SwordManState::AttackStart:
			AttackStartStart();
			break;
		case SwordManState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}
	ResetLiveTime();

	State = _State;
}


void SwordMan::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case SwordManDir::Right:
		AnimationName = "SwordManRight_";
		break;
	case SwordManDir::Left:
		AnimationName = "SwordManLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

unsigned int SwordMan::GetWallCheck()
{
	unsigned int WallColor = GetGroundColor(RGB(255, 255, 255), CheckPos);
	return WallColor;
}

void SwordMan::Movement(float _Delta)
{
	float4 MovePos1 = float4::ZERO;

	if (Dir == SwordManDir::Left)
	{
		CheckPos = { -40.0f, -40.0f };
		MovePos = { -Speed * _Delta, 0.0f };
		// ������
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = SwordManDir::Right;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}
	else if (Dir == SwordManDir::Right)
	{
		CheckPos = { 40.0f, -40.0f };
		MovePos = { Speed * _Delta, 0.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			Dir = SwordManDir::Left;
			ChangeAnimationState(CurState);
			return;
		}
		AddPos(MovePos);
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255))
		{
			// MovePos�� �ٲ������ ����� �������̰�.

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
}
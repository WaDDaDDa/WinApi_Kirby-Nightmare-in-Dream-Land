#include "WheelKirby.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "Bullet.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "BackGround.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineCollision.h>

WheelKirby::WheelKirby()
{

}

WheelKirby::~WheelKirby()
{

}

void WheelKirby::Start()
{
	// �ε� �Ǿ����� �ʴٸ� �ε��ϰ�, �ε� �Ǿ� �ִٸ� �ٽ� �ε����� �ʴ´�.
	// �ߺ� �ε��ϸ� ���� ��� �����.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("WheelKirbyLeft.bmp");
	if (false == IsResource)
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation ����
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WheelKirbyLeft.bmp"), 8, 37);
		}
		{ // RinghtAnimation ����
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WheelKirbyRight.bmp"), 8, 37);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Player);

	{ // LeftAnimation ����
		MainRenderer->CreateAnimation("WheelKirbyLeft_Idle", "WheelKirbyLeft.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_DownIdle", "WheelKirbyLeft.bmp", 10, 10, 0.2f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Walk", "WheelKirbyLeft.bmp", 28, 37, 0.05f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Jump", "WheelKirbyLeft.bmp", 51, 51, 0.2f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_JumpTurn", "WheelKirbyLeft.bmp", 52, 60, 0.03f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Falling", "WheelKirbyLeft.bmp", 61, 61, 0.1f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_FallingEnd", "WheelKirbyLeft.bmp", 10, 10, 0.1f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Run", "WheelKirbyLeft.bmp", 45, 52, 0.1f, true);  // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("WheelKirbyLeft_Fly", "WheelKirbyLeft.bmp", 71, 76, 0.1f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_BreathIn", "WheelKirbyLeft.bmp", 77, 81, 0.05f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_BreathOut", "WheelKirbyLeft.bmp", 81, 79, 0.05f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Tackle", "WheelKirbyLeft.bmp", 118, 118, 0.05f, false);
		MainRenderer->FindAnimation("WheelKirbyLeft_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("WheelKirbyLeft_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("WheelKirbyLeft_AttackStart", "WheelKirbyLeft.bmp", 174, 182, 0.05f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Attack", "WheelKirbyLeft.bmp", 228, 231, 0.05f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_JumpAttackStart", "WheelKirbyLeft.bmp", 174, 182, 0.05f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_JumpAttack", "WheelKirbyLeft.bmp", 228, 231, 0.05f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_DirChange", "WheelKirbyLeft.bmp", 234, 238, 0.03f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_OpenDoor", "WheelKirbyLeft.bmp", 122, 125, 0.2f, false);

	}

	{ // RightAnimation ����
		MainRenderer->CreateAnimation("WheelKirbyRight_Idle", "WheelKirbyRight.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_DownIdle", "WheelKirbyRight.bmp", 10, 11, 0.2f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_Walk", "WheelKirbyRight.bmp", 28, 37, 0.05f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_Jump", "WheelKirbyRight.bmp", 51, 51, 0.1f, false);
		MainRenderer->CreateAnimation("WheelKirbyRight_JumpTurn", "WheelKirbyRight.bmp", 52, 60, 0.03f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_Falling", "WheelKirbyRight.bmp", 61, 61, 0.1f, false);
		MainRenderer->CreateAnimation("WheelKirbyRight_FallingEnd", "WheelKirbyRight.bmp", 10, 10, 0.1f, false);
		MainRenderer->CreateAnimation("WheelKirbyRight_Run", "WheelKirbyRight.bmp", 45, 52, 0.1f, true); // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("WheelKirbyRight_Fly", "WheelKirbyRight.bmp", 71, 76, 0.1f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_BreathIn", "WheelKirbyRight.bmp", 77, 81, 0.05f, false);
		MainRenderer->CreateAnimation("WheelKirbyRight_BreathOut", "WheelKirbyRight.bmp", 81, 79, 0.05f, false);
		MainRenderer->CreateAnimation("WheelKirbyRight_Tackle", "WheelKirbyRight.bmp", 118, 118, 0.05f, false);
		MainRenderer->FindAnimation("WheelKirbyRight_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("WheelKirbyRight_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("WheelKirbyRight_AttackStart", "WheelKirbyRight.bmp", 174, 182, 0.05f, false);
		MainRenderer->CreateAnimation("WheelKirbyRight_Attack", "WheelKirbyRight.bmp", 228, 231, 0.05f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_JumpAttackStart", "WheelKirbyRight.bmp", 174, 182, 0.05f, false);
		MainRenderer->CreateAnimation("WheelKirbyRight_JumpAttack", "WheelKirbyRight.bmp", 228, 231, 0.05f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_DirChange", "WheelKirbyRight.bmp", 234, 238, 0.03f, false);
		MainRenderer->CreateAnimation("WheelKirbyRight_OpenDoor", "WheelKirbyRight.bmp", 122, 125, 0.2f, false);

	}

	// ���� �ִϸ��̼�
	{

	}

	{ // �浹ü ����
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionScale(BodyCollisionScale);
		BodyCollision->SetCollisionPos(BodyCollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);

		TackleCollision = CreateCollision(CollisionOrder::PlayerAttack);
		TackleCollision->SetCollisionScale(TackleCollisionScale);
		TackleCollision->SetCollisionPos(TackleCollisionPos);
		TackleCollision->SetCollisionType(CollisionType::CirCle);
		TackleCollision->Off();

		AttCollision = CreateCollision(CollisionOrder::SparkAttack);
		AttCollision->SetCollisionScale(AttCollisionScale);
		AttCollision->SetCollisionPos(AttCollisionPos);
		AttCollision->SetCollisionType(CollisionType::CirCle);
		AttCollision->Off();
	}

	MainRenderer->SetScaleRatio(4.0f);
	MainRenderer->SetTexture("Blank.bmp");
	SetOrder(UpdateOrder::Player);
	SetAbillity(Abillity::Wheel);
	// PlayerPos �� static ��� ���� ������ �ʱ� ��ġ�� �����ϰ� �����Ҽ�������.
	ChangeState(KirbyState::Idle);
}

void WheelKirby::LevelStart()
{
	Kirby::GetMainPlayer()->SetMainPlayer(this);
}

void WheelKirby::Update(float _Delta)
{
	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(GetOrder()))
	{
		return;
	}

	// �浹�Լ� �����.
	std::vector<GameEngineCollision*> _Col;

	if (true == BodyCollision->Collision(CollisionOrder::MonsterBody
		, _Col
		, CollisionType::CirCle // ���� �簢������ ����
		, CollisionType::CirCle // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			ChangeState(KirbyState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::MonsterFireAttack
		, _Col
		, CollisionType::CirCle // ���� �簢������ ����
		, CollisionType::CirCle // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			ChangeState(KirbyState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::MonsterSparkAttack
		, _Col
		, CollisionType::CirCle // ���� �簢������ ����
		, CollisionType::CirCle // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			ChangeState(KirbyState::Damage);
			return;
		}
	}

	if (true == BodyCollision->Collision(CollisionOrder::Portal
		, _Col
		, CollisionType::CirCle // ���� �簢������ ����
		, CollisionType::Rect // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			if (true == GameEngineInput::IsDown(VK_UP))
			{
				ChangeState(KirbyState::OpenDoor);
				return;
			}
		}
	}

	StateUpdate(_Delta);
	CameraFocus(_Delta);
}

void WheelKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case KirbyDir::Right:
		AnimationName = "WheelKirbyRight_";
		break;
	case KirbyDir::Left:
		AnimationName = "WheelKirbyLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

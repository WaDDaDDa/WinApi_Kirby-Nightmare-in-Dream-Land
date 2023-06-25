#include "SwordKirby.h"
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


SwordKirby::SwordKirby()
{

}

SwordKirby::~SwordKirby()
{

}

void SwordKirby::Start()
{
	// �ε� �Ǿ����� �ʴٸ� �ε��ϰ�, �ε� �Ǿ� �ִٸ� �ٽ� �ε����� �ʴ´�.
	// �ߺ� �ε��ϸ� ���� ��� �����.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("SwordKirbyLeft.bmp");
	if (false == IsResource)
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation ����
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SwordKirbyLeft.bmp"), 8, 24);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SwordKirbyLeft_Attack.bmp"), 8, 4);
		}
		{ // RinghtAnimation ����
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SwordKirbyRight.bmp"), 8, 24);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("SwordKirbyRight_Attack.bmp"), 8, 4);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	LeftAttRenderer = CreateRenderer(RenderOrder::Effect);
	RightAttRenderer = CreateRenderer(RenderOrder::Effect);

	{ // LeftAnimation ����
		MainRenderer->CreateAnimation("SwordKirbyLeft_Idle", "SwordKirbyLeft.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("SwordKirbyLeft_DownIdle", "SwordKirbyLeft.bmp", 10, 11, 0.2f, true);
		MainRenderer->CreateAnimation("SwordKirbyLeft_Tackle", "SwordKirbyLeft.bmp", 20, 21, 0.1f, true);
		MainRenderer->CreateAnimation("SwordKirbyLeft_Walk", "SwordKirbyLeft.bmp", 33, 44, 0.05f, true);
		MainRenderer->CreateAnimation("SwordKirbyLeft_Jump", "SwordKirbyLeft.bmp", 27, 28, 0.2f, true);
		MainRenderer->CreateAnimation("SwordKirbyLeft_JumpTurn", "SwordKirbyLeft.bmp", 83, 93, 0.03f, true);
		MainRenderer->CreateAnimation("SwordKirbyLeft_Falling", "SwordKirbyLeft.bmp", 94, 95, 0.1f, true);
		MainRenderer->CreateAnimation("SwordKirbyLeft_FallingEnd", "SwordKirbyLeft.bmp", 96, 96, 0.1f, false);
		MainRenderer->CreateAnimation("SwordKirbyLeft_Run", "SwordKirbyLeft.bmp", 45, 52, 0.1f, true);  // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("SwordKirbyLeft_Fly", "SwordKirbyLeft.bmp", 61, 68, 0.1f, true);
		MainRenderer->CreateAnimation("SwordKirbyLeft_BreathIn", "SwordKirbyLeft.bmp", 56, 60, 0.05f, false);
		MainRenderer->FindAnimation("SwordKirbyLeft_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("SwordKirbyLeft_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("SwordKirbyLeft_AttackStart", "SwordKirbyLeft_Attack.bmp", 0, 2, 0.1f, false);
		MainRenderer->CreateAnimation("SwordKirbyLeft_Attack", "SwordKirbyLeft_Attack.bmp", 5, 12, 0.05f, false);
		MainRenderer->CreateAnimation("SwordKirbyLeft_JumpAttackStart", "SwordKirbyLeft_Attack.bmp", 3, 4, 0.05f, false);
		MainRenderer->CreateAnimation("SwordKirbyLeft_JumpAttack", "SwordKirbyLeft_Attack.bmp", 17, 25, 0.05f, false);
		MainRenderer->CreateAnimation("SwordKirbyLeft_BreathOut", "SwordKirbyLeft.bmp", 79, 80, 0.1f, false);
	}

	{ // RightAnimation ����
		MainRenderer->CreateAnimation("SwordKirbyRight_Idle", "SwordKirbyRight.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("SwordKirbyRight_DownIdle", "SwordKirbyRight.bmp", 10, 11, 0.2f, true);
		MainRenderer->CreateAnimation("SwordKirbyRight_Tackle", "SwordKirbyRight.bmp", 20, 21, 0.1f, true);
		MainRenderer->CreateAnimation("SwordKirbyRight_Walk", "SwordKirbyRight.bmp", 33, 44, 0.05f, true);
		MainRenderer->CreateAnimation("SwordKirbyRight_Jump", "SwordKirbyRight.bmp", 27, 28, 0.1f, true);
		MainRenderer->CreateAnimation("SwordKirbyRight_JumpTurn", "SwordKirbyRight.bmp", 83, 93, 0.03f, true);
		MainRenderer->CreateAnimation("SwordKirbyRight_Falling", "SwordKirbyRight.bmp", 94, 95, 0.1f, true);
		MainRenderer->CreateAnimation("SwordKirbyRight_FallingEnd", "SwordKirbyRight.bmp", 96, 96, 0.1f, false);
		MainRenderer->CreateAnimation("SwordKirbyRight_Run", "SwordKirbyRight.bmp", 45, 52, 0.1f, true); // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("SwordKirbyRight_Fly", "SwordKirbyRight.bmp", 61, 68, 0.1f, true);
		MainRenderer->CreateAnimation("SwordKirbyRight_BreathIn", "SwordKirbyRight.bmp", 56, 60, 0.05f, false);
		MainRenderer->FindAnimation("SwordKirbyRight_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("SwordKirbyRight_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("SwordKirbyRight_AttackStart", "SwordKirbyRight_Attack.bmp", 0, 2, 0.1f, false);
		MainRenderer->CreateAnimation("SwordKirbyRight_Attack", "SwordKirbyRight_Attack.bmp", 5, 12, 0.05f, false);
		MainRenderer->CreateAnimation("SwordKirbyRight_JumpAttackStart", "SwordKirbyRight_Attack.bmp", 3, 4, 0.05f, false);
		MainRenderer->CreateAnimation("SwordKirbyRight_JumpAttack", "SwordKirbyRight_Attack.bmp", 17, 25, 0.05f, false);
		MainRenderer->CreateAnimation("SwordKirbyRight_BreathOut", "SwordKirbyRight.bmp", 79, 80, 0.1f, false);
	}
	// ���� �ִϸ��̼�
	{
		LeftAttRenderer->SetTexture("Blank.bmp");
		RightAttRenderer->SetTexture("Blank.bmp");
		LeftAttRenderer->CreateAnimation("LeftSwordBlank", "Blank.bmp", 0, 0, 0.1f, false);
		LeftAttRenderer->CreateAnimation("LeftSwordEffect", "LeftSwordEffect.bmp", 0, 6, 0.05f, false);
		RightAttRenderer->CreateAnimation("RightSwordBlank", "Blank.bmp", 0, 0, 0.1f, false);
		RightAttRenderer->CreateAnimation("RightSwordEffect", "RightSwordEffect.bmp", 0, 6, 0.05f, false);

		LeftAttRenderer->ChangeAnimation("LeftSwordEffect");
		LeftAttRenderer->SetRenderPos(LeftAttackCollisionPos);
		LeftAttRenderer->SetRenderScale(float4{ 600 , 400});
		LeftAttRenderer->ChangeAnimation("LeftSwordBlank");

		RightAttRenderer->ChangeAnimation("RightSwordEffect");
		RightAttRenderer->SetRenderPos(RightAttackCollisionPos);
		RightAttRenderer->SetRenderScale(float4{ 600 , 400 });
		RightAttRenderer->ChangeAnimation("RightSwordBlank");

	}

	{ // �浹ü ����
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionScale(BodyCollisionScale);
		BodyCollision->SetCollisionPos(BodyCollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);

		LeftAttackCollision = CreateCollision(CollisionOrder::SwordAttack);
		LeftAttackCollision->SetCollisionScale(LeftAttackCollisionScale);
		LeftAttackCollision->SetCollisionPos(LeftAttackCollisionPos);
		LeftAttackCollision->SetCollisionType(CollisionType::CirCle);
		LeftAttackCollision->Off();

		RightAttackCollision = CreateCollision(CollisionOrder::SwordAttack);
		RightAttackCollision->SetCollisionScale(RightAttackCollisionScale);
		RightAttackCollision->SetCollisionPos(RightAttackCollisionPos);
		RightAttackCollision->SetCollisionType(CollisionType::CirCle);
		RightAttackCollision->Off();

		JumpAttackCollision = CreateCollision(CollisionOrder::SwordAttack);
		JumpAttackCollision->SetCollisionScale(JumpAttackCollisionScale);
		JumpAttackCollision->SetCollisionPos(JumpAttackCollisionPos);
		JumpAttackCollision->SetCollisionType(CollisionType::CirCle);
		JumpAttackCollision->Off();

		TackleCollision = CreateCollision(CollisionOrder::PlayerAttack);
		TackleCollision->SetCollisionScale(TackleCollisionScale);
		TackleCollision->SetCollisionPos(TackleCollisionPos);
		TackleCollision->SetCollisionType(CollisionType::Rect);
		TackleCollision->Off();
	}

	MainRenderer->SetScaleRatio(4.0f);
	MainRenderer->SetTexture("Blank.bmp");
	SetOrder(UpdateOrder::Player);
	SetAbillity(Abillity::Sword);
	// PlayerPos �� static ��� ���� ������ �ʱ� ��ġ�� �����ϰ� �����Ҽ�������.
	ChangeState(KirbyState::Idle);
}

void SwordKirby::LevelStart()
{
	Kirby::GetMainPlayer()->SetMainPlayer(this);
	Kirby::GetMainPlayer()->OverOn();
}

void SwordKirby::Update(float _Delta)
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

	StateUpdate(_Delta);
	CameraFocus(_Delta);
}

void SwordKirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case KirbyDir::Right:
		AnimationName = "SwordKirbyRight_";
		break;
	case KirbyDir::Left:
		AnimationName = "SwordKirbyLeft_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

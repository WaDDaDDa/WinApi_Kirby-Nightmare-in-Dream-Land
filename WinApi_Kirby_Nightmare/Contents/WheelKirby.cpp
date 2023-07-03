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
	LeftAttRenderer = CreateRenderer(RenderOrder::Effect);
	RightAttRenderer = CreateRenderer(RenderOrder::Effect);

	{ // LeftAnimation ����
		MainRenderer->CreateAnimation("WheelKirbyLeft_Idle", "WheelKirbyLeft.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_DownIdle", "WheelKirbyLeft.bmp", 10, 10, 0.2f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Walk", "WheelKirbyLeft.bmp", 28, 37, 0.05f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Jump", "WheelKirbyLeft.bmp", 51, 51, 0.2f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_JumpTurn", "WheelKirbyLeft.bmp", 52, 60, 0.03f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Falling", "WheelKirbyLeft.bmp", 61, 61, 0.1f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_FallingEnd", "WheelKirbyLeft.bmp", 96, 96, 0.1f, false);
		MainRenderer->CreateAnimation("WheelKirbyLeft_Run", "WheelKirbyLeft.bmp", 45, 52, 0.1f, true);  // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("WheelKirbyLeft_Fly", "WheelKirbyLeft.bmp", 61, 68, 0.1f, true);
		MainRenderer->CreateAnimation("WheelKirbyLeft_BreathIn", "WheelKirbyLeft.bmp", 56, 60, 0.05f, false);
		MainRenderer->FindAnimation("WheelKirbyLeft_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("WheelKirbyLeft_BreathIn")->Inters[4] = 0.1f;
	}

	{ // RightAnimation ����
		MainRenderer->CreateAnimation("WheelKirbyRight_Idle", "WheelKirbyRight.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_DownIdle", "WheelKirbyRight.bmp", 10, 11, 0.2f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_Walk", "WheelKirbyRight.bmp", 33, 44, 0.05f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_Jump", "WheelKirbyRight.bmp", 27, 28, 0.1f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_JumpTurn", "WheelKirbyRight.bmp", 83, 93, 0.03f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_Falling", "WheelKirbyRight.bmp", 94, 95, 0.1f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_FallingEnd", "WheelKirbyRight.bmp", 96, 96, 0.1f, false);
		MainRenderer->CreateAnimation("WheelKirbyRight_Run", "WheelKirbyRight.bmp", 45, 52, 0.1f, true); // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("WheelKirbyRight_Fly", "WheelKirbyRight.bmp", 61, 68, 0.1f, true);
		MainRenderer->CreateAnimation("WheelKirbyRight_BreathIn", "WheelKirbyRight.bmp", 56, 60, 0.05f, false);
		MainRenderer->FindAnimation("WheelKirbyRight_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("WheelKirbyRight_BreathIn")->Inters[4] = 0.1f;
		
	}
	// ���� �ִϸ��̼�
	{
		LeftAttRenderer->SetTexture("Blank.bmp");
		RightAttRenderer->SetTexture("Blank.bmp");
		//LeftAttRenderer->CreateAnimation("LeftSwordBlank", "Blank.bmp", 0, 0, 0.1f, false);
		//LeftAttRenderer->CreateAnimation("LeftSwordEffect", "LeftSwordEffect.bmp", 0, 6, 0.05f, false);
		//RightAttRenderer->CreateAnimation("RightSwordBlank", "Blank.bmp", 0, 0, 0.1f, false);
		//RightAttRenderer->CreateAnimation("RightSwordEffect", "RightSwordEffect.bmp", 0, 6, 0.05f, false);

		//LeftAttRenderer->ChangeAnimation("LeftSwordEffect");
		//LeftAttRenderer->SetRenderPos(LeftAttackCollisionPos);
		//LeftAttRenderer->SetRenderScale(float4{ 600 , 400 });
		//LeftAttRenderer->ChangeAnimation("LeftSwordBlank");

		//RightAttRenderer->ChangeAnimation("RightSwordEffect");
		//RightAttRenderer->SetRenderPos(RightAttackCollisionPos);
		//RightAttRenderer->SetRenderScale(float4{ 600 , 400 });
		//RightAttRenderer->ChangeAnimation("RightSwordBlank");

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
	}

	MainRenderer->SetScaleRatio(4.0f);
	MainRenderer->SetTexture("Blank.bmp");
	SetOrder(UpdateOrder::Player);
	SetAbillity(Abillity::Sword);
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

			if (true == GameEngineInput::IsDown('W'))
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

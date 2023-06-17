#include "Kirby.h"
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
#include "MainHubLevel.h"
#include "BurningKirby.h"

Kirby* Kirby::MainPlayer = nullptr;

Kirby::Kirby()
{

}

Kirby::~Kirby()
{

}


void Kirby::Start()
{
	// �ε� �Ǿ����� �ʴٸ� �ε��ϰ�, �ε� �Ǿ� �ִٸ� �ٽ� �ε����� �ʴ´�.
	// �ߺ� �ε��ϸ� ���� ��� �����.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("KirbyIdel.bmp");
	if (false == IsResource)
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");
		
		{ // LeftAnimation ����
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Idel.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_DownIdel.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Tackle.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Walk.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Jump.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Run.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Fly.bmp"), 4, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_BreathIn.bmp"), 5, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Attack.bmp"), 6, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_StarIn.bmp"), 6, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_StarOut.bmp"), 5, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_FatIdle.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_FatWalk.bmp"), 4, 4);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_FatJump.bmp"), 4, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_BreathOut.bmp"), 6, 3);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Swallow.bmp"), 3, 3);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Damage.bmp"), 3, 3);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_FatDamage.bmp"), 4, 1);
		}
		{ // RinghtAnimation ����
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Idel.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_DownIdel.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Tackle.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Walk.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Jump.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Run.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Fly.bmp"), 4, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_BreathIn.bmp"), 5, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Attack.bmp"), 6, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_StarIn.bmp"), 6, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_StarOut.bmp"), 5, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_FatIdle.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_FatWalk.bmp"), 4, 4);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_FatJump.bmp"), 4, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_BreathOut.bmp"), 6, 3);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Swallow.bmp"), 3, 3);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Damage.bmp"), 3, 3);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_FatDamage.bmp"), 4, 1);

		}
		{
			//����Ʈ �ε�
			FilePath.MoveParentToExistsChild("Resource");
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Etc\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("DamageEffects.bmp"), 3, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Star.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("StarEffects.bmp"), 4, 1);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	{ // LeftAnimation ����
		MainRenderer->CreateAnimation("Left_Idle", "KirbyLeft_Idel.bmp", 0, 1, 0.2f, true);
		MainRenderer->FindAnimation  ("Left_Idle")->Inters[1] = 0.5f;
		MainRenderer->CreateAnimation("Left_DownIdle", "KirbyLeft_DownIdel.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Tackle", "KirbyLeft_Tackle.bmp", 0, 1, 0.1f, true);
		MainRenderer->FindAnimation("Left_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("Left_Walk", "KirbyLeft_Walk.bmp", 0, 9, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Jump", "KirbyLeft_Jump.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("Left_JumpTurn", "KirbyLeft_Jump.bmp", 1, 7, 0.03f, false);
		MainRenderer->CreateAnimation("Left_Falling", "KirbyLeft_Jump.bmp", 8, 8, 1.0f, false);
		MainRenderer->CreateAnimation("Left_FallingEnd", "KirbyLeft_Jump.bmp", 9, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Run", "KirbyLeft_Run.bmp", 0, 7, 0.1f, true);  // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("Left_Fly", "KirbyLeft_Fly.bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Left_BreathIn", "KirbyLeft_BreathIn.bmp", 0, 4, 0.05f, true);
		MainRenderer->FindAnimation("Left_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("Left_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("Left_AttackStart", "KirbyLeft_Attack.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Attack", "KirbyLeft_Attack.bmp", 3, 4, 0.05f, true);
		MainRenderer->CreateAnimation("Left_StarIn", "KirbyLeft_StarIn.bmp", 0, 5, 0.05f, true);
		MainRenderer->CreateAnimation("Left_StarOut", "KirbyLeft_StarOut.bmp", 0, 4, 0.05f, true);
		MainRenderer->CreateAnimation("Left_FatIdle", "KirbyLeft_FatIdle.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("Left_FatWalk", "KirbyLeft_FatWalk.bmp", 0, 15, 0.05f, true);
		MainRenderer->CreateAnimation("Left_FatJump", "KirbyLeft_FatJump.bmp", 1, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Left_FatJumpTurn", "KirbyLeft_FatJump.bmp", 2, 4, 0.1f, false);
		MainRenderer->CreateAnimation("Left_FatFalling", "KirbyLeft_FatJump.bmp", 5, 6, 0.1f, false);
		MainRenderer->CreateAnimation("Left_FatFallingEnd", "KirbyLeft_FatJump.bmp", 7, 7, 0.1f, false);
		MainRenderer->CreateAnimation("Left_BreathOut", "KirbyLeft_BreathOut.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Left_Swallow", "KirbyLeft_Swallow.bmp", 0, 7, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Damage", "KirbyLeft_Damage.bmp", 0, 8, 0.05f, false);
		MainRenderer->CreateAnimation("Left_FatDamage", "KirbyLeft_FatDamage.bmp", 0, 3, 0.1f, false);
	}

	{ // RightAnimation ����
		MainRenderer->CreateAnimation("Right_Idle", "KirbyRight_Idel.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("Right_DownIdle", "KirbyRight_DownIdel.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Tackle", "KirbyRight_Tackle.bmp", 0, 1, 0.1f, true);
		MainRenderer->FindAnimation("Right_Tackle")->Inters[0] = 0.5f;
		MainRenderer->CreateAnimation("Right_Walk", "KirbyRight_Walk.bmp", 0, 9, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Jump", "KirbyRight_Jump.bmp", 0, 0, 0.1f, false);
		MainRenderer->CreateAnimation("Right_JumpTurn", "KirbyRight_Jump.bmp", 1, 7, 0.03f, false);
		MainRenderer->CreateAnimation("Right_Falling", "KirbyRight_Jump.bmp", 8, 8, 1.0f, false);
		MainRenderer->CreateAnimation("Right_FallingEnd", "KirbyRight_Jump.bmp", 9, 9, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Run", "KirbyRight_Run.bmp", 0, 7, 0.1f, true); // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("Right_Fly", "KirbyRight_Fly.bmp", 0, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Right_BreathIn", "KirbyRight_BreathIn.bmp", 0, 4, 0.05f, true);
		MainRenderer->FindAnimation("Right_BreathIn")->Inters[3] = 0.1f;
		MainRenderer->FindAnimation("Right_BreathIn")->Inters[4] = 0.1f;
		MainRenderer->CreateAnimation("Right_AttackStart", "KirbyRight_Attack.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Attack", "KirbyRight_Attack.bmp", 3, 4, 0.05f, true);
		MainRenderer->CreateAnimation("Right_StarIn", "KirbyRight_StarIn.bmp", 0, 5, 0.05f, true);
		MainRenderer->CreateAnimation("Right_StarOut", "KirbyRight_StarOut.bmp", 0, 4, 0.05f, true);
		MainRenderer->CreateAnimation("Right_FatIdle", "KirbyRight_FatIdle.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("Right_FatWalk", "KirbyRight_FatWalk.bmp", 0, 15, 0.05f, true);
		MainRenderer->CreateAnimation("Right_FatJump", "KirbyRight_FatJump.bmp", 1, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Right_FatJumpTurn", "KirbyRight_FatJump.bmp", 2, 4, 0.1f, false);
		MainRenderer->CreateAnimation("Right_FatFalling", "KirbyRight_FatJump.bmp", 5, 6, 0.1f, false);
		MainRenderer->CreateAnimation("Right_FatFallingEnd", "KirbyRight_FatJump.bmp", 7, 7, 0.1f, false);
		MainRenderer->CreateAnimation("Right_BreathOut", "KirbyRight_BreathOut.bmp", 0, 1, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Swallow", "KirbyRight_Swallow.bmp", 0, 7, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Damage", "KirbyRight_Damage.bmp", 0, 8, 0.05f, false);
		MainRenderer->CreateAnimation("Right_FatDamage", "KirbyRight_FatDamage.bmp", 0, 3, 0.1f, false);
	}

	{ // �浹ü ����
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionScale(BodyCollisionScale);
		BodyCollision->SetCollisionPos(BodyCollisionPos);
		BodyCollision->SetCollisionType(CollisionType::CirCle);
		AttackCollision = CreateCollision(CollisionOrder::VacumAttack);
		AttackCollision->SetCollisionScale(AttackCollisionScale);
		AttackCollision->SetCollisionPos(AttackCollisionPos);
		AttackCollision->SetCollisionType(CollisionType::Rect);
		AttackCollision->Off();
	}
	MainRenderer->SetScaleRatio(4.0f);
	
	// PlayerPos �� static ��� ���� ������ �ʱ� ��ġ�� �����ϰ� �����Ҽ�������.
	ChangeState(KirbyState::Idle);
}

void Kirby::Update(float _Delta)
{

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

			if (State == KirbyState::FatFalling ||
				State == KirbyState::FatFallingEnd ||
				State == KirbyState::FatIdle ||
				State == KirbyState::FatJump ||
				State == KirbyState::FatJumpTurn ||
				State == KirbyState::FatWalk)
			{
				ChangeState(KirbyState::FatDamage);
				return;
			}

			ChangeState(KirbyState::Damage);
			return;
		}
	}

	// �� �� �ƿ� ���
	if (true == GameEngineInput::IsPress('L'))
	{
		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);

		// Monster::AllMonsterDeath();
	}

	if (true == GameEngineInput::IsPress('Y'))
	{
		//GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		// GameEngineLevel::CollisionDebugRenderSwitch();
	}

	CameraFocus(_Delta);
	StateUpdate(_Delta);
	Immune();
}


void Kirby::StateUpdate(float _Delta)
{
	switch (State)
	{
	case KirbyState::Idle:
		return IdleUpdate(_Delta);
	case KirbyState::DownIdle:
		return DownIdleUpdate(_Delta);
	case KirbyState::Tackle:
		return TackleUpdate(_Delta);
	case KirbyState::Walk:
		return WalkUpdate(_Delta);
	case KirbyState::Jump:
		return JumpUpdate(_Delta);
	case KirbyState::JumpTurn:
		return JumpTurnUpdate(_Delta);
	case KirbyState::Falling:
		return FallingUpdate(_Delta);
	case KirbyState::FallingEnd:
		return FallingEndUpdate(_Delta);
	case KirbyState::Run:
		return RunUpdate(_Delta);
	case KirbyState::Fly:
		return FlyUpdate(_Delta);
	case KirbyState::BreathIn:
		return BreathInUpdate(_Delta);
	case KirbyState::AttackStart:
		return AttackStartUpdate(_Delta);
	case KirbyState::Attack:
		return AttackUpdate(_Delta);
	case KirbyState::StarIn:
		return StarInUpdate(_Delta);
	case KirbyState::StarOut:
		return StarOutUpdate(_Delta);
	case KirbyState::FatIdle:
		return FatIdleUpdate(_Delta);
	case KirbyState::FatWalk:
		return FatWalkUpdate(_Delta);
	case KirbyState::FatJump:
		return FatJumpUpdate(_Delta);
	case KirbyState::FatJumpTurn:
		return FatJumpTurnUpdate(_Delta);
	case KirbyState::FatFalling:
		return FatFallingUpdate(_Delta);
	case KirbyState::FatFallingEnd:
		return FatFallingEndUpdate(_Delta);
	case KirbyState::BreathOut:
		return BreathOutUpdate(_Delta);
	case KirbyState::Swallow:
		return SwallowUpdate(_Delta);
	case KirbyState::Damage:
		return DamageUpdate(_Delta);
	case KirbyState::FatDamage:
		return FatDamageUpdate(_Delta);
	default:
		break;
	}
}

void Kirby::ChangeState(KirbyState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case KirbyState::Idle:
			IdleStart();
			break;
		case KirbyState::DownIdle:
			DownIdleStart();
			break;
		case KirbyState::Tackle:
			TackleStart();
			break;
		case KirbyState::Walk:
			WalkStart();
			break;
		case KirbyState::Jump:
			JumpStart();
			break;
		case KirbyState::JumpTurn:
			JumpTurnStart();
			break;
		case KirbyState::Falling:
			FallingStart();
			break;
		case KirbyState::FallingEnd:
			FallingEndStart();
			break;
		case KirbyState::Run:
			RunStart();
			break;
		case KirbyState::Fly:
			FlyStart();
			break;
		case KirbyState::BreathIn:
			BreathInStart();
			break;
		case KirbyState::AttackStart:
			AttackStartStart();
			break;
		case KirbyState::Attack:
			AttackStart();
			break;
		case KirbyState::StarIn:
			StarInStart();
			break;
		case KirbyState::StarOut:
			StarOutStart();
			break;
		case KirbyState::FatIdle:
			FatIdleStart();
			break;
		case KirbyState::FatWalk:
			FatWalkStart();
			break;
		case KirbyState::FatJump:
			FatJumpStart();
			break;
		case KirbyState::FatJumpTurn:
			FatJumpTurnStart();
			break;
		case KirbyState::FatFalling:
			FatFallingStart();
			break;
		case KirbyState::FatFallingEnd:
			FatFallingEndStart();
			break;		
		case KirbyState::BreathOut:
			BreathOutStart();
			break;
		case KirbyState::Swallow:
			SwallowStart();
			break;
		case KirbyState::Damage:
			DamageStart();
			break;
		case KirbyState::FatDamage:
			FatDamageStart();
			break;
		default:
			break;
		}
	}

	ResetLiveTime();

	State = _State;
}


void Kirby::DirCheck()
{
	// �ڵ���� ���������� ����Ǳ� ������ 
	// D�� �������·� A������������ ������ȯ�� ����������
	// A�� �������·� D�� ������������ A�� ó���� ���� �̷������ ������ȯ�� �����ʱ⶧���� ������ �߻��ߴ�.

	// ������ �����ϴ� Ű���� ��� ������� �׻��� �״�� ����. �Ʒ��� D�� �����϶� Left�� �Ǵ� ���� ����.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}
	
	// A�� ���Ȱų� D�� �����̶�� Left�� ������ȯ �ε� �������־ Left�� �ٶ󺸴� ������ ����.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = KirbyDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	// D�� ���Ȱų� A�� �����̸� Right�� ���� ��ȯ.
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = KirbyDir::Right;
		ChangeAnimationState(CurState);
		return;
	}
}

void Kirby::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

	switch (Dir)
	{
	case KirbyDir::Right:
		AnimationName = "Right_";
		break;
	case KirbyDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

void Kirby::CameraFocus(float _Delta)
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	int CameraRangeX = GetLevel()->GetMainCamera()->GetPos().iX();
	int CameraRangeY = GetLevel()->GetMainCamera()->GetPos().iY();

	int PlayerX = GetPos().iX();
	int PlayerY = GetPos().iY();

	float ImageX = GetGroundTexture()->GetScale().X - 960.0f;
	float ImageY = GetGroundTexture()->GetScale().Y - 600.0f;
	
	// ī�޶� ���� �������� ��������.
	if (0 >= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ 0.0f, GetLevel()->GetMainCamera()->GetPos().Y});
	}
	// ī�޶� ���� ������ �ִ�ġ�� ��������.
	if (ImageX <= GetLevel()->GetMainCamera()->GetPos().X)
	{
		GetLevel()->GetMainCamera()->SetPos({ ImageX, GetLevel()->GetMainCamera()->GetPos().Y });
	}

	if (ImageY <= GetLevel()->GetMainCamera()->GetPos().Y)
	{
		GetLevel()->GetMainCamera()->SetPos({ GetLevel()->GetMainCamera()->GetPos().X, ImageY });
	}
	
	// ī�޶� �����̴� X ���� 250 ~ 650 ���̿�ĳ���͸� �д�.
	// ī�޶��� �ӵ��� ĳ������ �ӵ��� �Ѵ�.
	if (650 < PlayerX - CameraRangeX)
	{
		GetLevel()->GetMainCamera()->AddPos({ Speed * _Delta , 0});
	}
	else if (250 > PlayerX - CameraRangeX)
	{
		GetLevel()->GetMainCamera()->AddPos({- Speed * _Delta , 0 });
	}

	// ī�޶� �����̴� Y���� ĳ���Ͱ� -200 ~ -450 ���̿��� �����δ�.
	// ĳ���� �̵��ӵ��� ī�޶� ���� �������� �߷��� �ӵ��� �Ѵ�.
	if (-200 < CameraRangeY - PlayerY)
	{
		if (GetGravityVector().iY() <= -1)
		{
			GetLevel()->GetMainCamera()->AddPos(GetGravityVector() * _Delta);
			return;
		}
		GetLevel()->GetMainCamera()->AddPos(float4::UP);
	}
	else if (-450 > CameraRangeY - PlayerY)
	{
		if (GetGravityVector().iY() >= 1 )
		{
			GetLevel()->GetMainCamera()->AddPos(GetGravityVector() * _Delta);
			return;
		}
		GetLevel()->GetMainCamera()->AddPos(float4::DOWN);
	}
}

void Kirby::LevelStart()
{
	MainPlayer = this;
}

void Kirby::ChangeKirby(Abillity _Kirby)
{
	if (GetAbillity() != _Kirby)
	{
		float4 CurPos = MainPlayer->GetPos();
		float4 CurPrevPos = MainPlayer->GetPrevPos();

		switch (_Kirby)
		{
		case Abillity::Normal:
			MainPlayer->Death();
			SetMainPlayer(MainPlayer->GetLevel()->CreateActor<Kirby>());
			break;
		case Abillity::Burning:
			MainPlayer->Death();
			SetMainPlayer(MainPlayer->GetLevel()->CreateActor<BurningKirby>());
			break;
		default:
			break;
		}

		MainPlayer->SetPrevPos(CurPrevPos);
		MainPlayer->SetPos(CurPos);
		MainPlayer->SetGroundTexture(GetGroundTexture());
		MainPlayer->OverOn();
	}

	MainPlayer->SetAbillity(_Kirby);
}

unsigned int Kirby::GetWallCheck()
{
	unsigned int WallColor = GetGroundColor(RGB(255, 255, 255), CheckPos);
	return WallColor;
}

void Kirby::Movement(float _Delta)
{
	if (true == GameEngineInput::IsPress('A') && Dir == KirbyDir::Left)
	{
		//CameraFocus();
		CheckPos = { -40.0f, -40.0f };
		MovePos = { -Speed * _Delta, 0.0f };

		// ������
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(MovePos);
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == KirbyDir::Right)
	{
		//CameraFocus();
		CheckPos = { 40.0f, -40.0f };

		MovePos = { Speed * _Delta, 0.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
		}
		AddPos(MovePos);
	}
}

// �ؽ�Ʈ ����ؼ� Ȯ���ϴ� ���.
void Kirby::Render(float _Delta)
{
	std::string Text = "�÷��̾� ������ġ : ";

	Text += std::to_string(GetPos().X);
	Text += ", ";
	Text += std::to_string(GetPos().Y);
	Text += "  ī�޶� ������ġ :";
	Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().X);
	Text += ", ";
	Text += std::to_string(GetLevel()->GetMainCamera()->GetPos().Y);
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
}

void Kirby::Immune()
{
	if (true == ImmuneValue)
	{
		RenderSwitch();
		BodyCollision->Off();
		if (0.6f <= GetLiveTime())
		{
			ImmuneValue = false;
			BodyCollision->On();
			MainRenderer->On();
		}
	}
}

void Kirby::RenderSwitch()
{
	static float Sec = 0.0f;
	static bool RenderValue = true;
	Sec += GetLiveTime();

	if (0.2f <= Sec)
	{
		RenderValue = !RenderValue;
		Sec = 0.0f;
	}

	if (RenderValue == true)
	{
		MainRenderer->On();
		return;
	}
	else if (RenderValue == false)
	{
		MainRenderer->Off();
		return;
	}

}
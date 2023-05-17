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
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Walk.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Jump.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Run.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Fly.bmp"), 4, 2);
		}
		// ��� ������.
		{ // RinghtAnimation ����
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Idel.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Walk.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Jump.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Run.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Fly.bmp"), 4, 2);
		}



	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetScaleRatio(2.0f);

	{ // LeftAnimation ����
		MainRenderer->CreateAnimation("Left_Idle", "KirbyLeft_Idel.bmp", 0, 1, 1.0f, true);
		MainRenderer->CreateAnimation("Left_Walk", "KirbyLeft_Walk.bmp", 0, 9, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Jump", "KirbyLeft_Jump.bmp", 0, 9, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Run", "KirbyLeft_Run.bmp", 0, 7, 0.1f, true);  // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("Left_Fly", "KirbyLeft_Fly.bmp", 0, 7, 0.1f, true);
	}

	{ // RightAnimation ����
		MainRenderer->CreateAnimation("Right_Idle", "KirbyRight_Idel.bmp", 0, 1, 1.0f, true);
		MainRenderer->CreateAnimation("Right_Walk", "KirbyRight_Walk.bmp", 0, 9, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Jump", "KirbyRight_Jump.bmp", 0, 9, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Run", "KirbyRight_Run.bmp", 0, 7, 0.1f, true); // 8�� �극��ũ��� 9�� ���浹
		MainRenderer->CreateAnimation("Right_Fly", "KirbyRight_Fly.bmp", 0, 7, 0.1f, true);
	}

	MainRenderer->ChangeAnimation("Right_Idle");

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	// PlayerPos �� static ��� ���� ������ �ʱ� ��ġ�� �����ϰ� �����Ҽ�������.
	float4 PlayerPos = WinScale.Half() + float4({ -250, 130});

	SetPos(PlayerPos);

	ChangeState(KirbyState::Idle);

}

void Kirby::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Kirby::StateUpdate(float _Delta)
{
	switch (State)
	{
	case KirbyState::Idle:
		return IdleUpdate(_Delta);
	case KirbyState::Walk:
		return WalkUpdate(_Delta);
	case KirbyState::Jump:
		return JumpUpdate(_Delta);
	case KirbyState::Run:
		return JumpUpdate(_Delta);
	case KirbyState::Fly:
		return JumpUpdate(_Delta);
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
		case KirbyState::Walk:
			WalkStart();
			break;
		case KirbyState::Jump:
			JumpStart();
			break;
		case KirbyState::Run:
			RunStart();
			break;
		case KirbyState::Fly:
			FlyStart();
			break;
		default:
			break;
		}
	}

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
	// "Idle"
	// _StateName

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

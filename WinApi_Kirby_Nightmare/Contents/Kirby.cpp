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

Kirby* Kirby::MainPlayer = nullptr;

Kirby::Kirby()
{

}

Kirby::~Kirby()
{

}


void Kirby::Start()
{
	// 로딩 되어있지 않다면 로드하고, 로딩 되어 있다면 다시 로드하지 않는다.
	// 중복 로드하면 릭이 계속 생긴다.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("KirbyIdel.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");
		
		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\Left\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Idel.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_UnderIdel.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Walk.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Jump.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Run.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyLeft_Fly.bmp"), 4, 2);
		}
		{ // RinghtAnimation 셋팅
			FilePath.MoveParentToExistsChild("Right");
			FilePath.MoveChild("Right\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Idel.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_UnderIdel.bmp"), 2, 1);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Walk.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Jump.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Run.bmp"), 5, 2);
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyRight_Fly.bmp"), 4, 2);
		}
	}

	MainRenderer = CreateRenderer(RenderOrder::Play);
	MainRenderer->SetScaleRatio(4.0f);
	SetPos(float4{360,360});

	{ // LeftAnimation 생성
		MainRenderer->CreateAnimation("Left_Idle", "KirbyLeft_Idel.bmp", 0, 1, 0.2f, true);
		MainRenderer->FindAnimation  ("Left_Idle")->Inters[1] = 0.5f;
		MainRenderer->CreateAnimation("Left_UnderIdle", "KirbyLeft_UnderIdel.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("Left_Walk", "KirbyLeft_Walk.bmp", 0, 9, 0.05f, true);
		MainRenderer->CreateAnimation("Left_Jump", "KirbyLeft_Jump.bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("Left_JumpTurn", "KirbyLeft_Jump.bmp", 1, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Falling", "KirbyLeft_Jump.bmp", 8, 8, 1.0f, true);
		MainRenderer->CreateAnimation("Left_FallingEnd", "KirbyLeft_Jump.bmp", 9, 9, 0.1f, true);
		MainRenderer->CreateAnimation("Left_Run", "KirbyLeft_Run.bmp", 0, 7, 0.1f, true);  // 8은 브레이크모션 9는 벽충돌
		MainRenderer->CreateAnimation("Left_Fly", "KirbyLeft_Fly.bmp", 0, 7, 0.1f, true);
	}

	{ // RightAnimation 생성
		MainRenderer->CreateAnimation("Right_Idle", "KirbyRight_Idel.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("Right_UnderIdle", "KirbyRight_UnderIdel.bmp", 0, 1, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Walk", "KirbyRight_Walk.bmp", 0, 9, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Jump", "KirbyRight_Jump.bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("Right_JumpTurn", "KirbyRight_Jump.bmp", 1, 7, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Falling", "KirbyRight_Jump.bmp", 8, 8, 1.0f, true);
		MainRenderer->CreateAnimation("Right_FallingEnd", "KirbyRight_Jump.bmp", 9, 9, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Run", "KirbyRight_Run.bmp", 0, 7, 0.1f, true); // 8은 브레이크모션 9는 벽충돌
		MainRenderer->CreateAnimation("Right_Fly", "KirbyRight_Fly.bmp", 0, 7, 0.1f, true);
	}
	// PlayerPos 는 static 멤버 변수 선언후 초기 위치를 선언하고 시작할수있을듯.
	ChangeState(KirbyState::Idle);
}

void Kirby::Update(float _Delta)
{
	StateUpdate(_Delta);

	CameraFocus();
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
		default:
			break;
		}
	}

	State = _State;
}


void Kirby::DirCheck()
{
	// 코드들이 순차적으로 실행되기 때문에 
	// D를 누른상태로 A를눌렀을때의 방향전환은 가능하지만
	// A를 누른상태로 D를 눌렀을때에는 A의 처리가 먼저 이루어져서 방향전환이 되지않기때문에 문제가 발생했다.

	// 방향을 결정하는 키들이 모두 프리라면 그상태 그대로 유지. 아래의 D가 프리일때 Left가 되는 것을 방지.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}
	
	// A가 눌렸거나 D가 프리이라면 Left로 방향전환 인데 가만히있어도 Left를 바라보는 현상이 생김.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = KirbyDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	// D가 눌렸거나 A가 프리이면 Right로 방향 전환.
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

void Kirby::CameraFocus()
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	int CameraRangeX = GetLevel()->GetMainCamera()->GetPos().iX();
	int CameraRangeY = GetLevel()->GetMainCamera()->GetPos().iY();

	int PlayerX = GetPos().iX();
	int PlayerY = GetPos().iY();

	if (650 < PlayerX - CameraRangeX || 250 > PlayerX - CameraRangeX)
	{
		GetLevel()->GetMainCamera()->AddPos({ MovePos.X, 0});
	}

	if (-200 < CameraRangeY - PlayerY)
	{
		GetLevel()->GetMainCamera()->AddPos({ 0, MovePos.Y });
	}
	else if (-450 > CameraRangeY - PlayerY)
	{
		GetLevel()->GetMainCamera()->AddPos(GetGravityVector());
	}
}


void Kirby::LevelStart()
{
	MainPlayer = this;
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
		CameraFocus();
		CheckPos = { -40.0f, -40.0f };
		MovePos = { -Speed * _Delta, 0.0f };

		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			return;
		}
		AddPos(MovePos);

	}
	else if (true == GameEngineInput::IsPress('D') && Dir == KirbyDir::Right)
	{
		CameraFocus();
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
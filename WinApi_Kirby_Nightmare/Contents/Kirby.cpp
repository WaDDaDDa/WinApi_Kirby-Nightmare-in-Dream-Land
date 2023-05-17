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
	// 로딩 되어있지 않다면 로드하고, 로딩 되어 있다면 다시 로드하지 않는다.
	// 중복 로드하면 릭이 계속 생긴다.
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("Kirby.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");
		// 경로 까지만.
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyIdel.bmp"), 2, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyWalk.bmp"), 10, 1);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Kirby.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TestMonster1.Bmp"));
	}

	MainRenderer = CreateRenderer("Kirby.bmp",RenderOrder::Play);
	//MainRenderer->SetRenderScale({ 64, 64 });  // 없으면 기본 이미지 크기 그대로 출력

	MainRenderer->CreateAnimation("Idle", "KirbyIdel.bmp", 0 , 1, 1.0f, true);
	MainRenderer->CreateAnimation("run", "KirbyWalk.bmp", 0, 9, 0.1f, true);
	MainRenderer->ChangeAnimation("Idle");

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	// PlayerPos 는 static 멤버 변수 선언후 초기 위치를 선언하고 시작할수있을듯.
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
	case KirbyState::Run:
		return RunUpdate(_Delta);
	case KirbyState::Shoot:
		return ShootUpdate(_Delta);
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
		case KirbyState::Run:
			RunStart();
			break;
		case KirbyState::Shoot:
			ShootStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}
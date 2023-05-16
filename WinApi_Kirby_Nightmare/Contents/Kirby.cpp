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
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("Kirby.bmp");
	if (false == IsResource)
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");
		// ��� ������.
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Kirby\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyIdel.bmp"), 2, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("KirbyWalk.bmp"), 10, 1);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Kirby.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TestMonster1.Bmp"));
	}

	MainRenderer = CreateRenderer("Kirby.bmp",RenderOrder::Play);
	//MainRenderer->SetRenderScale({ 64, 64 });  // ������ �⺻ �̹��� ũ�� �״�� ���

	MainRenderer->CreateAnimation("Idle", "KirbyIdel.bmp", 0 , 1, 1.0f, true);
	MainRenderer->CreateAnimation("run", "KirbyWalk.bmp", 0, 9, 0.1f, true);
	MainRenderer->ChangeAnimation("Idle");

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
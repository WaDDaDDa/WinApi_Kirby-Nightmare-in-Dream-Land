#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include "BackGround.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	bool IsResource = ResourcesManager::GetInst().IsLoadTexture("Untitled.bmp");
	if (false == IsResource)
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		{ // LeftAnimation 셋팅
			FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Backgrounds\\");
			ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Untitled.bmp"), 2, 1);
		}
	}

	CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("Untitled.Bmp");
	CurBackGround->SetAnimation("Title", "Untitled.Bmp", 0, 1, 0.2f, true);

	CurBackGround->SetPos({480,300});
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('P') ||
		true == GameEngineInput::IsDown('Q') ||
		true == GameEngineInput::IsDown('W') ||
		true == GameEngineInput::IsDown('E') ||
		true == GameEngineInput::IsDown('R') ||
		true == GameEngineInput::IsDown('T') ||
		true == GameEngineInput::IsDown('Y') ||
		true == GameEngineInput::IsDown('U') ||
		true == GameEngineInput::IsDown('I') ||
		true == GameEngineInput::IsDown('O') ||
		true == GameEngineInput::IsDown('A') ||
		true == GameEngineInput::IsDown('S') ||
		true == GameEngineInput::IsDown('D') ||
		true == GameEngineInput::IsDown('F') ||
		true == GameEngineInput::IsDown('G') ||
		true == GameEngineInput::IsDown('H') ||
		true == GameEngineInput::IsDown('J') ||
		true == GameEngineInput::IsDown('L') ||
		true == GameEngineInput::IsDown('Z') ||
		true == GameEngineInput::IsDown('X') ||
		true == GameEngineInput::IsDown('C') ||
		true == GameEngineInput::IsDown('V') ||
		true == GameEngineInput::IsDown('B') ||
		true == GameEngineInput::IsDown('N') ||
		true == GameEngineInput::IsDown('M'))
	{
		GameEngineCore::ChangeLevel("MainHubLevel");
	}
}
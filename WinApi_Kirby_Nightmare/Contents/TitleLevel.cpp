#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include "BackGround.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	BackGround* CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("TestTitle.Bmp");
	CurBackGround->SetPos({360,240});
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainHubLevel");
	}
}
#include "MainHubLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>


// Contents
#include "Kirby.h"
#include "Stage.h"
#include "BackGround.h"

MainHubLevel::MainHubLevel()
{

}

MainHubLevel::~MainHubLevel()
{

}

void MainHubLevel::Start()
{
	 //이미지가 로드되지않았다면 로드하고 로드 되었다면 로드안하기 위함.
	if (false == ResourcesManager::GetInst().IsLoadTexture("TestBackGround.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Stages\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TestStage_Debug3.bmp"));
	}

	BackGround* CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("TestBackGround.Bmp");
	StagePtr = CreateActor<Stage>();
	StagePtr->Init("TestStage3.Bmp", "TestStage_Debug3.bmp");

	LevelPlayer = CreateActor<Kirby>();

}


void MainHubLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		StagePtr->SwitchRender();
	}

}
void MainHubLevel::Render()
{
}
void MainHubLevel::Release()
{
}

void MainHubLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	LevelPlayer->SetGroundTexture("TestStage_Debug3.bmp");

	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y
	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void MainHubLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
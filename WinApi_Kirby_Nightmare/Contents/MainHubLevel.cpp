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
	// 플레이 레벨이 만들어졌다.
	// 이 레벨에는 뭐가 있어야지?
	// 플레이어 만들고
	// 맵만들고
	// 몬스터 만들고
	// 액터

	// 자기 임의대로 만들겠다는 것이고 xxxxx
	// Player* NewPlayer = new Player();
	// 객체가 create될때 모든것을 준비한다.
	BackGround* CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("TestBackGround.Bmp");
	Stage* CurStage = CreateActor<Stage>();
	CurStage->Init("TestStage1.Bmp");

	LevelPlayer = CreateActor<Kirby>();

}


void MainHubLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
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

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y
	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void MainHubLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
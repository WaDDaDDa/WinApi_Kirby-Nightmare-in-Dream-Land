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
	// �÷��� ������ ���������.
	// �� �������� ���� �־����?
	// �÷��̾� �����
	// �ʸ����
	// ���� �����
	// ����

	// �ڱ� ���Ǵ�� ����ڴٴ� ���̰� xxxxx
	// Player* NewPlayer = new Player();
	// ��ü�� create�ɶ� ������ �غ��Ѵ�.
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
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
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
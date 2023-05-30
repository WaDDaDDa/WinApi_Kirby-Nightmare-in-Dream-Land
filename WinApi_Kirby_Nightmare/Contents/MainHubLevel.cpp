#include "MainHubLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "UIManager.h"


// Contents
#include "Kirby.h"
#include "Stage.h"
#include "BackGround.h"
#include "Monster.h"
#include "WaddleDee.h"

MainHubLevel::MainHubLevel()
{

}

MainHubLevel::~MainHubLevel()
{

}

void MainHubLevel::Start()
{
	GetMainCamera()->SetPos(float4{ 0, -100 });
	GameEngineSound::SetGlobalVolume(SoundVolume);
	 //�̹����� �ε�����ʾҴٸ� �ε��ϰ� �ε� �Ǿ��ٸ� �ε���ϱ� ����.
	if (false == ResourcesManager::GetInst().IsLoadTexture("TestBackGround.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Stages\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Level1_Debug.bmp"));
	}

	if (nullptr == GameEngineSound::FindSound("04Vegetable_Valley.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Sounds\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("04Vegetable_Valley.mp3"));
	}

	BackGround* CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("TestBackGround.Bmp");
	StagePtr = CreateActor<Stage>();
	StagePtr->Init("Level1.Bmp", "Level1_Debug.bmp");


	LevelPlayer = CreateActor<Kirby>();
	LevelPlayer->OverOn();
	CreateActor<UIManager>();

}


void MainHubLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
		
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		CreateActor<WaddleDee>();
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		StagePtr->SwitchRender();
		CollisionDebugRenderSwitch();
	}

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

	LevelPlayer->SetGroundTexture("Level1_Debug.bmp");

	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");

	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y
	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void MainHubLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
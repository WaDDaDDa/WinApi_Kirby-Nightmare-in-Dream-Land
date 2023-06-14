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
#include "BurningKirby.h"

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
	if (false == ResourcesManager::GetInst().IsLoadTexture("MainHup.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.MoveParentToExistsChild("Resource");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Stages\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MainHupDebug.bmp"));
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
	CurBackGround->Init("MainHupBackGround.Bmp");
	StagePtr = CreateActor<Stage>();
	StagePtr->Init("MainHup.Bmp", "MainHupDebug.bmp");

	LevelPlayer = CreateActor<Kirby>();
	//LevelPlayer->OverOn();
	CreateActor<UIManager>();
}


void MainHubLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("VegetableValleyLevel");
		LevelPlayer->SetGroundTexture("Level1_Debug.bmp");
		BGMPlayer.Stop();
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("MainHupDebug.bmp");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		StagePtr->SwitchRender();
		CollisionDebugRenderSwitch();
	}

	if (true == GameEngineInput::IsDown('Q'))
	{
		float4 PrevPos = LevelPlayer->GetPos();
		LevelPlayer->Death();
		LevelPlayer = CreateActor<BurningKirby>();
		LevelPlayer->SetPos(PrevPos);
		LevelPlayer->SetGroundTexture("MainHupDebug.bmp");
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

	LevelPlayer->SetGroundTexture("MainHupDebug.bmp");

	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");
}

void MainHubLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
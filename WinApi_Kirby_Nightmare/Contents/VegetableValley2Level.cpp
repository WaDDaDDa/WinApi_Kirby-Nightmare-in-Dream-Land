#include "VegetableValley2Level.h"
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
#include "Portal.h"
#include "MainHubLevel.h"

VegetableValley2Level::VegetableValley2Level()
{

}

VegetableValley2Level::~VegetableValley2Level()
{

}

void VegetableValley2Level::Start()
{
	//이미지가 로드되지않았다면 로드하고 로드 되었다면 로드안하기 위함.
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

	CreateActor<UIManager>();
	MainPortal = CreateActor<Portal>();
	MainPortal->SetPos(float4{ 3900, 290 });

	// 몬스터 배치
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level1_Debug.bmp");
		Waddle->SetPos(float4{ 1500,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level1_Debug.bmp");
		Waddle->SetPos(float4{ 2600,350 });
	}

}


void VegetableValley2Level::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
		BGMPlayer.Stop();

	}

	if (true == GameEngineInput::IsDown('M'))
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level1_Debug.bmp");
		Waddle->SetPos(float4{ 500,360 });
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		StagePtr->SwitchRender();
		CollisionDebugRenderSwitch();
	}

	std::vector<GameEngineCollision*> _Col;

	if (true == MainPortal->BodyCollision->Collision(CollisionOrder::PlayerBody
		, _Col
		, CollisionType::Rect // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			if (true == GameEngineInput::IsDown('W'))
			{
				GameEngineCore::ChangeLevel("MainHubLevel");
				MainHubLevel::LevelPlayer->SetGroundTexture("MainHupDebug.bmp");
				MainHubLevel::LevelPlayer->SetPos(MainHubLevel::LevelPlayer->GetPrevPos());
				MainHubLevel::LevelPlayer->SetPrevPos(MainHubLevel::LevelPlayer->GetPos());
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}
}


void VegetableValley2Level::Release()
{

}

void VegetableValley2Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == MainHubLevel::LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	MainHubLevel::LevelPlayer->SetGroundTexture("Level1_Debug.bmp");
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(MainHubLevel::LevelPlayer->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");
}

void VegetableValley2Level::LevelEnd(GameEngineLevel* _NextLevel)
{

}
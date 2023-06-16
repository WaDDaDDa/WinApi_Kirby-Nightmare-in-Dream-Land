#include "VegetableValleyLevel.h"
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

class Kirby* VegetableValleyLevel::LevelPlayer = nullptr;

VegetableValleyLevel::VegetableValleyLevel()
{

}

VegetableValleyLevel::~VegetableValleyLevel()
{

}

void VegetableValleyLevel::Start()
{
	//GetMainCamera()->SetPos(float4{ 0, -100 });
	GameEngineSound::SetGlobalVolume(SoundVolume);
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

	LevelPlayer = CreateActor<Kirby>();
	LevelPlayer->OverOn();
	CreateActor<UIManager>();
	MainPortal = CreateActor<Portal>();
	MainPortal->SetPos(float4{ 3900, 290 });
}


void VegetableValleyLevel::Update(float _Delta)
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

			if (true == GameEngineInput::IsPress('W'))
			{
				GameEngineCore::ChangeLevel("MainHubLevel");
				LevelPlayer->SetGroundTexture("MainHupDebug.bmp");
				LevelPlayer->SetPrevPos(LevelPlayer->GetPos());
				LevelPlayer->SetPos(float4 { 500 , 800 });
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}
}


void VegetableValleyLevel::Release()
{

}

void VegetableValleyLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	/*if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}*/

	LevelPlayer->SetGroundTexture("Level1_Debug.bmp");
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetMainCamera()->SetPos(LevelPlayer->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
	//GetMainCamera()->SetPos(float4{ VegetableValleyLevel::LevelPlayer->GetPos().Half().X, -VegetableValleyLevel::LevelPlayer->GetPos().Half().Y });
	//BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");
}

void VegetableValleyLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
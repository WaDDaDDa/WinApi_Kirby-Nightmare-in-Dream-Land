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
#include "BurningMonster.h"
#include "FadeObject.h"

VegetableValley2Level::VegetableValley2Level()
{

}

VegetableValley2Level::~VegetableValley2Level()
{

}

void VegetableValley2Level::Start()
{
	if (nullptr == GameEngineSound::FindSound("04Vegetable_Valley.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resource");
		FilePath.MoveChild("Resource\\Kirby_Nightmare_in_Dream_Land\\Sounds\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("04Vegetable_Valley.mp3"));
	}

	CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("TestBackGround.Bmp");
	CurBackGround->SetScale("TestBackGround.Bmp", 4.0f);

	StagePtr = CreateActor<Stage>();
	StagePtr->Init("Level2.Bmp", "Level2_Debug.bmp");

	CreateActor<UIManager>();
	MainPortal = CreateActor<Portal>();
	MainPortal->SetPos(float4{ 4750, 360 });
}


void VegetableValley2Level::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainHubLevel");
		Kirby::GetMainPlayer()->SetGroundTexture("MainHupDebug.bmp");
		float4 Ppos = Kirby::GetMainPlayer()->GetPos();
		Kirby::GetMainPlayer()->SetPos(Kirby::GetMainPlayer()->GetPrevPos());
		Kirby::GetMainPlayer()->SetPrevPos(Ppos);
		BGMPlayer.Stop();
		return;
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 500,360 });
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		StagePtr->SwitchRender();
	}

	if (true == GameEngineInput::IsDown('K'))
	{
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
				GameEngineCore::ChangeLevel("VegetableValley3Level");
				Kirby::GetMainPlayer()->SetGroundTexture("Level3_Debug.bmp");
				float4 Ppos = Kirby::GetMainPlayer()->GetPos();
				//Kirby::GetMainPlayer()->SetPos(Kirby::GetMainPlayer()->GetPrevPos());
				Kirby::GetMainPlayer()->SetPos(float4{ 330, 640 });
				Kirby::GetMainPlayer()->SetPrevPos(Ppos);
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
	Monster::AllMonsterDeath();

	if (nullptr == Kirby::GetMainPlayer())
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	Kirby::GetMainPlayer()->SetGroundTexture("Level2_Debug.bmp");
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();

	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");
	FadeObject* FObject = CreateActor<FadeObject>();
	FObject->FadeIn();
	// 몬스터 배치
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 1500,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 2600,350 });
	}
	{
		BurningMonster* Waddle = CreateActor<BurningMonster>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 800,350 });
	}
	{
		BurningMonster* Waddle = CreateActor<BurningMonster>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 3600,350 });
	}

}

void VegetableValley2Level::LevelEnd(GameEngineLevel* _NextLevel)
{

}
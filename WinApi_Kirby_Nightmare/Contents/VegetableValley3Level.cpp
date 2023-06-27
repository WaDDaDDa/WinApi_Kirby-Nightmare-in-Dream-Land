#include "VegetableValley3Level.h"
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

VegetableValley3Level::VegetableValley3Level()
{

}

VegetableValley3Level::~VegetableValley3Level()
{

}

void VegetableValley3Level::Start()
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
	StagePtr->Init("Level3.Bmp", "Level3_Debug.bmp");

	CreateActor<UIManager>();
	MainPortal = CreateActor<Portal>();
	MainPortal->SetPos(float4{ 4750, 360 });
}


void VegetableValley3Level::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainHubLevel");
		BGMPlayer.Stop();
		return;
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level3_Debug.bmp");
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
				GameEngineCore::ChangeLevel("VegetableValleyLevel");
				BGMPlayer.Stop();
				return;
			}
			return;
		}
	}
}


void VegetableValley3Level::Release()
{

}

void VegetableValley3Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	Monster::AllMonsterDeath();

	if (nullptr == Kirby::GetMainPlayer())
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}
	// BGM 및 페이드 인
	BGMPlayer = GameEngineSound::SoundPlay("04Vegetable_Valley.mp3");
	FadeObject* FObject = CreateActor<FadeObject>();
	FObject->FadeIn();

	// 커비 셋팅 . 이전능력 폼체인지
	Abillity CurAbill = Kirby::GetMainPlayer()->GetAbillity();
	Kirby::GetMainPlayer()->Death();
	Kirby::GetMainPlayer()->SetMainPlayer(CreateActor<Kirby>());
	Kirby::GetMainPlayer()->ChangeKirby(CurAbill);
	Kirby::GetMainPlayer()->SetGroundTexture("Level3_Debug.bmp");
	Kirby::GetMainPlayer()->SetPos(StartPos);

	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });

	// 몬스터 배치
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level3_Debug.bmp");
		Waddle->SetPos(float4{ 1500,350 });
	}
	{
		BurningMonster* Waddle = CreateActor<BurningMonster>();
		Waddle->SetGroundTexture("Level3_Debug.bmp");
		Waddle->SetPos(float4{ 2600,350 });
	}

}

void VegetableValley3Level::LevelEnd(GameEngineLevel* _NextLevel)
{

}
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
#include "BGMPlayer.h"
#include "SparkMonster.h"

VegetableValley2Level::VegetableValley2Level()
{

}

VegetableValley2Level::~VegetableValley2Level()
{

}

void VegetableValley2Level::Start()
{
	CurBackGround = CreateActor<BackGround>();
	CurBackGround->Init("TestBackGround.Bmp");
	CurBackGround->SetScale("TestBackGround.Bmp", 4.0f);

	StagePtr = CreateActor<Stage>();
	StagePtr->Init("Level2.Bmp", "Level2_Debug.bmp");

	MainPortal = CreateActor<Portal>();
	MainPortal->Door->Off();
	MainPortal->SubDoor->ChangeAnimation("BlackDoor");
	MainPortal->SubDoor->SetScaleRatio(1.0f);
	MainPortal->SetPos(PortalPos);
}


void VegetableValley2Level::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainHubLevel");
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
				MainPortal->SetCurLevel("VegetableValley3Level");
				return;
			}
			return;
		}
	}

	if (Kirby::GetMainPlayer()->GetLife() != UIManager::UI->GetCurLife())
	{
		GameEngineTime::MainTimer.SetAllTimeScale(1.0f);
		LevelStart(this);
		return;
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

	FadeObject* FObject = CreateActor<FadeObject>();
	FObject->FadeIn();

	BGMPlayer::ChangeBGM("04Vegetable_Valley.mp3");

	Abillity CurAbill = Kirby::GetMainPlayer()->GetAbillity();
	int KirbyLife = Kirby::GetMainPlayer()->GetLife();

	Kirby::GetMainPlayer()->Death();
	Kirby::GetMainPlayer()->SetMainPlayer(CreateActor<Kirby>());
	Kirby::GetMainPlayer()->ChangeKirby(CurAbill);
	Kirby::GetMainPlayer()->SetGroundTexture("Level2_Debug.bmp");
	Kirby::GetMainPlayer()->SetPos(StartPos);
	Kirby::GetMainPlayer()->SetLife(KirbyLife);

	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetMainCamera()->SetPos(Kirby::GetMainPlayer()->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });

	// 몬스터 배치
	{
		BurningMonster* Waddle = CreateActor<BurningMonster>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 800,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 1500,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 1520,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 1540,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 1560,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 1580,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 1600,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 1480,350 });
	}
	{
		WaddleDee* Waddle = CreateActor<WaddleDee>();
		Waddle->SetGroundTexture("Level2_Debug.bmp");
		Waddle->SetPos(float4{ 2600,350 });
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